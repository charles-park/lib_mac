# lib_mac
MAC adress를 odroid_factory_api를 통하여 Control하는 Library

mac_server_ctrl을 JIG Lib2.0에 맞게 refactoring.

ODROID Mac Request server control app

### need package
* ubuntu package : build-essential, git, vim, python3, python3-pip
* python module : aiohttp, asyncio
```
roor@server:~/# pip install aiohttp asyncio
```
```
# Python3 control app
roor@server:~/lib_mac# python3 mac_server_ctrl.py -h

usage : python3 mac_server_ctl.py [-D | -F][-r | -e] {board name} [-e:mac]
      [option1] -D : Developer server api
                -F : Factory server api
      [option2] -r : request mac addr
                -i : server info display
                -e : erase mac addr [option3 {erase mac addr}]
      [option3] if option2 == -e
                   Set erase mac address 
      e.g) python3 mac_server_ctl.py -D -r m1s   : dev-server control for test
           python3 mac_server_ctl.py -F -r m1s   : factory-server control for product.
           python3 mac_server_ctl.py -D -e m1s 001e06xxxxxx

* API_SERVER_HOST    (option1 == -F) = http://192.168.0.118:8880
* API_DEV_SERVER_HOST(option1 == -D) = http://192.168.0.118:8881
```
```
# Lib single app
roor@server:~/lib_mac# ./lib_mac -h

Usage: ./lib_mac [-F | -D] [-B:Board name] [-r | -e] [(-r:mac | uuid) | (-e:mac_addr)]

  -F --factory        *** warning *** : factory server ctrl
  -D --developer      developer server ctrl
  -B --board_name     request board name.
  -r --request        request from server. (mac or uuid)
  -e --erase          request erase mac.

  e.g) request mac or uuid
       lib_mac [-D:Developer | -F:Factory] -B [Board:m1s] -r [mac | uuid]
  e.g) erase mac or uuid
       lib_mac [-D:Developer | -F:Factory] -B [Board:m1s] -e [mac addr:001e06xxxxxx]
```
