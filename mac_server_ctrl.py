#
# Mac server control test app. charles.park 2022/04/21
#
import sys
import os
import asyncio

from odroid_factory_api import API_MANAGER

# API_SERVER_HOST = 'https://factory.hardkernel.kro.kr:8880'
# API_TEST_SERVER_HOST = 'https://factory-dev.hardkernel.kro.kr:8880'
#
# 2023.09.18 변경
#
# 내부서버 192.168.0.118을 사용하도록 수정되었음 (개발용포트 : 8881, 생산용포트 : 8880).
#
API_SERVER_HOST = 'http://192.168.0.118:8880'
API_TEST_SERVER_HOST = 'http://192.168.0.118:8881'

def usage_print():
    print ('usage : python3 mac_server_ctl.py [-D | -F][-r | -e] {board name} [-e:mac]')
    print ('      [option1] -D : Developer server api')
    print ('                -F : Factory server api')
    print ('      [option2] -r : request mac addr')
    print ('                -i : server info display')
    print ('                -e : erase mac addr [option3 {erase mac addr}]')
    print ('      [option3] if option2 == -e')
    print ('                   Set erase mac address ')
    print ('      e.g) python3 mac_server_ctl.py -D -r m1s   : dev-server control for test')
    print ('           python3 mac_server_ctl.py -F -r m1s   : factory-server control for product.')
    print ('           python3 mac_server_ctl.py -D -e m1s 001e06xxxxxx')
    print ('')
    print ('* API_SERVER_HOST    (option1 == -F) = http://192.168.0.118:8880')
    print ('* API_DEV_SERVER_HOST(option1 == -D) = http://192.168.0.118:8881')
    print ('')
    quit()

if __name__ == "__main__":
    args = sys.argv

    args_cnt = len(args)
    board_name = 'None'
    uuid = 'None'

    if args_cnt < 3:
        usage_print()

    # odroid mac server control class get
    if args[1] == '-F':
        api_manager = API_MANAGER(board=args[3], server_host=API_SERVER_HOST)
    elif args[1] == '-D':
        api_manager = API_MANAGER(board=args[3], server_host=API_TEST_SERVER_HOST)
    else :
        print ('error, option1 [-D or -F]\n')
        quit()

    if (args[2] == '-r' and args_cnt != 4) or (args[2] == '-e' and args_cnt != 5) :
        print('')
        print('** Error argument count : args count = ', f'{args_cnt}', ' ***')
        print('')
        usage_print()

    # Log message disaplay control (1 = enable)
    api_manager.log_en(0)

    # api infomation (server info) display
    api_manager.info_print()

    if args[2] == '-r':
        if args_cnt != 4:
            usage_print()
        # get mac address for board-name from the mac server.
        uuid = asyncio.run(api_manager.request_mac_addr())
        if "error" in uuid :
            print ('error, request_mac_addr()!\n', uuid)
            quit()
        else :
            # info update
            asyncio.run(api_manager.update_record({'uuid': uuid}))
    elif args[2] == '-e':
        if args_cnt != 5:
            usage_print()

        # remove current mac address info or set mac address
        if '001e06' in args[4] and len(args[4]) == 12:
            api_manager.clear(args[3])
            api_manager.set_mac_addr (args[4])
            msg = asyncio.run(api_manager.delete_assigned_sign())
        else:
            print ('error, input mac addr,', f'input mac = {args[3]}, mac len = {len(args[3])}')
            quit()

        if "error" in msg:
            print ('error, delete_assigned_sign()', msg)
        else :
            ret_msg = 'success' + ',' + 'delete_assigned_sign()'+ ','
            ret_msg = ret_msg + args[3] + ',' + args[4]
            print (ret_msg)
        quit()
    else :
        print ("error, unknown message", f'args[1] = {args[1]}, args[2] = {args[2]}, args[3] = {args[3]}')
        quit()

    # mac display
    if "001e06" in uuid:
        ret_msg = 'success,'
    else :
        ret_msg = 'error,'

    ret_msg = ret_msg + 'mac_addr,' + api_manager.mac_addr + ',' + 'uuid,' + api_manager.uuid_mac
    print (ret_msg)
