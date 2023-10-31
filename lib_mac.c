//------------------------------------------------------------------------------
/**
 * @file lib_mac.c
 * @author charles-park (charles.park@hardkernel.com)
 * @brief ODROID Mac Request server control application.
 * @version 0.2
 * @date 2023-09-18
 *
 * @package apt install python3 python3-pip
 *          python3 -m pip install aiohttp asyncio
 *
 * @copyright Copyright (c) 2022
 *
 */
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <getopt.h>

#include "lib_mac.h"

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Debug msg
//------------------------------------------------------------------------------
#if defined (__LIB_SINGLE_APP__)
    #define dbg_msg(fmt, args...)   printf(fmt, ##args)
#else
    #define dbg_msg(fmt, args...)
#endif

#define	MAC_SERVER_CTRL_PYTHON_FILE_NAME	"mac_server_ctrl.py"
#define CMD_PRINT_WORKING_DIRECTORY         "pwd"
#define	CMD_LINE_CHARS	128

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// 문자열 변경 함수. 입력 포인터는 반드시 메모리가 할당되어진 변수여야 함.
//------------------------------------------------------------------------------
static void tolowerstr (char *p)
{
    int i, c = strlen(p);

    for (i = 0; i < c; i++, p++)
        *p = tolower(*p);
}

//------------------------------------------------------------------------------
static void toupperstr (char *p)
{
    int i, c = strlen(p);

    for (i = 0; i < c; i++, p++)
        *p = toupper(*p);
}

//------------------------------------------------------------------------------
// return 0 : find success, 1 : not found
//------------------------------------------------------------------------------
static int find_file_path (const char *fname, char *file_path)
{
    FILE *fp;
    char cmd_line[CMD_LINE_CHARS];

    // python send command setup
    memset (cmd_line, 0, sizeof(cmd_line));
    sprintf(cmd_line, "%s\n", CMD_PRINT_WORKING_DIRECTORY);

    if (NULL != (fp = popen(cmd_line, "r"))) {
        memset (cmd_line, 0, sizeof(cmd_line));
        fgets  (cmd_line, CMD_LINE_CHARS, fp);
        pclose (fp);

        strncpy (file_path, cmd_line, strlen(cmd_line)-1);

        // python send command setup
        memset (cmd_line, 0, sizeof(cmd_line));
        sprintf(cmd_line, "find -name %s\n", fname);
        if (NULL != (fp = popen(cmd_line, "r"))) {
            memset (cmd_line, 0, sizeof(cmd_line));
            fgets  (cmd_line, CMD_LINE_CHARS, fp);
            pclose (fp);
            if (strlen(cmd_line)) {
                strncpy (&file_path[strlen(file_path)], &cmd_line[1], strlen(cmd_line)-1);
                file_path[strlen(file_path)-1] = ' ';
                // Display full path (control python file)
                dbg_msg ("full path = %s\n", file_path);
                return 1;
            }
            dbg_msg ("file not found.");
            return 0;
        } else {
            printf ("error, %s file not found!!\n", fname);
        }
    }
    pclose(fp);
    return 0;
}

//------------------------------------------------------------------------------
int mac_server_request (const char ctrl_server,
                        const char req_type,
                        const char *board,
                        char *mac_uuid)
{
    FILE *fp;
    char cmd_line[CMD_LINE_CHARS *2], ctrl_file[CMD_LINE_CHARS];

    // find python control file
    memset (ctrl_file, 0, sizeof(ctrl_file));
    if (!find_file_path (MAC_SERVER_CTRL_PYTHON_FILE_NAME, ctrl_file))
        return 0;

    // python send command setup
    // python3 ctrl.py [-D|-F] [-r|-e] {board name} [-e:mac_addr]
    memset (cmd_line, 0, sizeof(cmd_line));
    sprintf(cmd_line, "python3 %s %s %s %s %s\n",
            ctrl_file,
            ctrl_server == MAC_SERVER_FACTORY ? "-F" : "-D",
            req_type    == REQ_TYPE_ERASE     ? "-e" : "-r",
            board,
            req_type    == REQ_TYPE_ERASE     ? mac_uuid : "");

    // command line display
    dbg_msg ("cmd_line : %s\n", cmd_line);

    if (NULL != (fp = popen(cmd_line, "r"))) {
        // command buffer init
        memset(cmd_line, 0, sizeof(cmd_line));
        while (fgets(cmd_line, 4096, fp)) {
            if (strstr(cmd_line, "success") != NULL) {
                if (req_type != REQ_TYPE_ERASE) {
                    char *p = strstr(cmd_line, "001e06");
                    /* mac request buffer size = uuid size(36 bytes) */
                    memset (mac_uuid, 0x00, REQ_TYPE_UUID_SIZE+1);
                    strncpy (mac_uuid,
                            /*
                                python response data:
                                success,mac_addr,001e06530012,uuid,3aaef75c-a164-433b-8d34-001e06530012
                                001e06부터 uuid까지의 offset은 18bytes (001e06xxxxxx = 12 bytes, ',uuid,' = 6 bytes)
                            */
                            (req_type == REQ_TYPE_UUID) ? (p + 18) : (p),
                            (req_type == REQ_TYPE_UUID) ? REQ_TYPE_UUID_SIZE : REQ_TYPE_MAC_SIZE);
                    // Display response msg from python control file.
                    dbg_msg ("response = %s\n", p);
                    toupperstr (mac_uuid);
                }
                pclose(fp);
                return 1;
            }
        }
    }
    pclose(fp);
    return 0;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
