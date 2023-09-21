//------------------------------------------------------------------------------
/**
 * @file lib_mac.h
 * @author charles-park (charles.park@hardkernel.com)
 * @brief ODROID Mac server control application.
 * @version 0.2
 * @date 2023-09-18
 *
 * @package apt install python3 python3-pip
 *          python3 -m pip install aiohttp asyncio
 *
 */
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#ifndef __LIB_MAC_H__
#define __LIB_MAC_H__

//------------------------------------------------------------------------------
#define MAC_SERVER_DEVELOPER    0
#define MAC_SERVER_FACTORY      1

#define REQ_TYPE_UNKNOWN        -1

#define REQ_TYPE_MAC            0
#define REQ_TYPE_MAC_SIZE       12

#define REQ_TYPE_UUID           1
#define REQ_TYPE_UUID_SIZE      36

#define REQ_TYPE_ERASE          2
#define REQ_TYPE_ERASE_SIZE     REQ_TYPE_MAC_SIZE

//------------------------------------------------------------------------------
//	function prototype
//------------------------------------------------------------------------------
extern int mac_server_request ( const char ctrl_server,
                                const char req_type,
                                const char *board,
                                char *mac_uuid);

//------------------------------------------------------------------------------
#endif  // #ifndef __LIB_MAC_H__
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
