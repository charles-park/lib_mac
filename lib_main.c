//------------------------------------------------------------------------------
/**
 * @file lib_main.c
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
#if defined(__LIB_SINGLE_APP__)
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
static void print_usage(const char *prog)
{
    puts("");
    printf("Usage: %s [-F | -D] [-B:Board name] [-r | -e] [(-r:mac | uuid) | (-e:mac_addr)]\n", prog);
    puts("");
    puts("  -F --factory        *** warning *** : factory server ctrl\n"
         "  -D --developer      developer server ctrl\n"
         "  -B --board_name     request board name.\n"
         "  -r --request        request from server. (mac or uuid)\n"
         "  -e --erase          request erase mac.\n"
         "\n"
         "  e.g) request mac or uuid\n"
         "       lib_mac [-D:Developer | -F:Factory] -B [Board:m1s] -r [mac | uuid]\n"
         "  e.g) erase mac or uuid\n"
         "       lib_mac [-D:Developer | -F:Factory] -B [Board:m1s] -e [mac addr:001e06xxxxxx]\n"
    );
    exit(1);
}

//------------------------------------------------------------------------------
/* Control server variable */
//------------------------------------------------------------------------------
static int   OPT_MAC_SERVER     = REQ_TYPE_UNKNOWN;
static char *OPT_REQ_BOARD      = "";
static char *OPT_ERASE_MACADDR  = "";
static int   OPT_REQ_TYPE       = REQ_TYPE_UNKNOWN;

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
static void parse_opts (int argc, char *argv[])
{
    while (1) {
        static const struct option lopts[] = {
            { "factory",    0, 0, 'F' },
            { "developer",  0, 0, 'D' },
            { "board_name", 1, 0, 'B' },
            { "request",    1, 0, 'r' },
            { "erase",      1, 0, 'e' },
            { NULL, 0, 0, 0 },
        };
        int c;

        c = getopt_long(argc, argv, "B:r:e:FDh", lopts, NULL);

        if (c == -1)
            break;

        switch (c) {
        case 'F':
            OPT_MAC_SERVER = MAC_SERVER_FACTORY;
            break;
        case 'D':
            OPT_MAC_SERVER = MAC_SERVER_DEVELOPER;
            break;
        case 'B':
            OPT_REQ_BOARD = optarg;
            break;
        case 'r':
            if      (!strncmp("mac",  optarg, strlen("mac")))
                OPT_REQ_TYPE = REQ_TYPE_MAC;
            else if (!strncmp("uuid", optarg, strlen("iiod")))
                OPT_REQ_TYPE = REQ_TYPE_UUID;	// read uuid
            else
                OPT_REQ_TYPE = REQ_TYPE_UNKNOWN;
            break;
        case 'e':
            OPT_ERASE_MACADDR = optarg;
            OPT_REQ_TYPE = REQ_TYPE_ERASE;	// erase
            tolowerstr(OPT_ERASE_MACADDR);
            break;
        case 'h':
        default:
            print_usage(argv[0]);
            break;
        }
    }
}

//------------------------------------------------------------------------------
int main(int argc, char **argv)
{
    char mac_uuid[REQ_TYPE_UUID_SIZE +1], ret;

    parse_opts(argc, argv);

    if ((OPT_REQ_BOARD  == NULL) ||
        (OPT_REQ_TYPE   == REQ_TYPE_UNKNOWN) ||
        (OPT_MAC_SERVER == REQ_TYPE_UNKNOWN)) {
        printf ("error : Unknown arguments.\n");
        printf ("Use the '-h' command to display help\n");
        return 0;
    }

    ret = mac_server_request (OPT_MAC_SERVER,
                            OPT_REQ_TYPE,
                            OPT_REQ_BOARD,
                            OPT_REQ_TYPE == REQ_TYPE_ERASE ? OPT_ERASE_MACADDR : mac_uuid);

    printf ("%s, SERVER=%s, REQ_BOARD=%s, REQ_TYPE=%s, MAC_UUID=%s\n",
        ret ? "success" : "error",
        OPT_MAC_SERVER ? "Factory" : "Developer",
        OPT_REQ_BOARD,
        OPT_REQ_TYPE == REQ_TYPE_ERASE ? "Erase" : "MAC or UUID",
        OPT_REQ_TYPE == REQ_TYPE_ERASE ? OPT_ERASE_MACADDR : mac_uuid);

    return 0;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#endif  // #if defined(__LIB_SINGLE_APP__)
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
