# API_SERVER_HOST = 'https://factory.hardkernel.kro.kr:8880'
# API_TEST_SERVER_HOST = 'https://factory-dev.hardkernel.kro.kr:8880'
#
# 2023.09.18 변경
#
# 내부서버 192.168.0.118을 사용하도록 수정되었음 (개발용포트 : 8881, 생산용포트 : 8880).
#
API_SERVER_HOST = 'http://192.168.0.118:8880'
API_TEST_SERVER_HOST = 'http://192.168.0.118:8881'

API_USER_INFO = {
    'username': 'odroid',
    'password': 'hard4624',
}

API_POST_URL = {
    'login': '/restapi/login',
    'request': '/restapi/request',
    'update': '/restapi/update',
    'delete': '/restapi/delete',
    'criteria': '/restapi/criteria',
    'counts': '/restapi/counts',
}

MAC_TABLES_BY_BOARD = {
    'xu4': [
        '001e0630',
        '001e0631',
        '001e0632',
        '001e0636',
        '001e0637',
        '001e0638',
        '001e0639',
    ],
    'hc1': [
        '001e0630',
        '001e0631',
        '001e0632',
        '001e0636',
        '001e0637',
        '001e0638',
        '001e0639',
    ],
    'hc2': [
        '001e0630',
        '001e0631',
        '001e0632',
        '001e0636',
        '001e0637',
        '001e0638',
        '001e0639',
    ],
    'n2': [
        '001e0642',
        '001e0643',
        '001e0644',
    ],
    'c4': [
        '001e0648',
    ],
    'hc4': [
        '001e0649',
    ],
    'm1': [
        '001e0651',
    ],
    'm1s': [
        '001e0653',
    ],
}

TABLE_FIELDS_BY_BOARD = {
    'xu4': [
        'mac_num',
        'assigned',
        'assigned_date',
        'board',
    ],
    'n2': [
        'mac_num',
        'assigned',
        'assigned_date',
        'board',
        'uuid',
        'ram',
        'usb_firmware',
        'usb_3_0_bandwidth',
        'usb_3_1_bandwidth',
        'usb_3_2_bandwidth',
        'usb_3_3_bandwidth',
        'usb_3_0_file_io_pass',
        'usb_3_1_file_io_pass',
        'usb_3_2_file_io_pass',
        'usb_3_3_file_io_pass',
        'usb_2_bandwidth',
        'usb_2_communicate_pass',
        'ethernet_bandwidth',
        'ethernet_ping_pass',
        'hdmi_cec_pass',
        'hdmi_i2c_pass',
        'fan_pass',
        'gpio_pass',
        'gpio_fail',
        'adc_pass',
        'adc_fail',
        'led_ethernet_amber_pass',
        'led_ethernet_green_pass',
        'led_power_pass',
        'led_system_pass',
        'ir_pass',
        'audio_pass',
        'slide_switch_pass',
        'iperf_rx_udp_bandwidth',
        'iperf_rx_udp_loss_rate',
        'rsync_transfer_speed',
        'all_pass'
    ],
    'c4': [
        'mac_num',
        'assigned',
        'assigned_date',
        'board',
        'uuid',
        'ram',
        'usb_firmware',
        'usb_3_0_bandwidth',
        'usb_3_1_bandwidth',
        'usb_3_2_bandwidth',
        'usb_3_3_bandwidth',
        'usb_3_0_file_io_pass',
        'usb_3_1_file_io_pass',
        'usb_3_2_file_io_pass',
        'usb_3_3_file_io_pass',
        'usb_2_bandwidth',
        'usb_2_communicate_pass',
        'ethernet_bandwidth',
        'ethernet_ping_pass',
        'hdmi_cec_pass',
        'hdmi_i2c_pass',
        'fan_pass',
        'gpio_pass',
        'gpio_fail',
        'adc_pass',
        'adc_fail',
        'led_ethernet_amber_pass',
        'led_ethernet_green_pass',
        'led_power_pass',
        'led_system_pass',
        'ir_pass',
        'audio_pass',
        'slide_switch_pass',
        'iperf_rx_udp_bandwidth',
        'iperf_rx_udp_loss_rate',
        'rsync_transfer_speed',
        'all_pass'
    ],
    'hc4': [
        'mac_num',
        'assigned',
        'assigned_date',
        'board',
        'uuid',
        'ethernet_bandwidth',
        'ethernet_ping',
        'iperf_rx_udp_bandwidth',
        'iperf_rx_udp_loss_rate',
        'lspci_sata_recognition',
        'sata0_read_speed',
        'sata0_write_speed',
        'sata0_file_integrity',
        'sata1_read_speed',
        'sata1_write_speed',
        'sata1_file_integrity',
        'usb_2_bandwidth',
        'led_system',
        'led_power',
        'led_hdd',
        'hdmi_edid_sda',
        'hdmi_edid_scl',
        'hdmi_cec',
        'hdmi_hpd',
        'power_5v',
        'power_3_3v',
        'power_vdeee',
        'fan_pwm',
        'fan_tacho',
        'header_5pin_io',
        'all_pass'
    ],
    'm1': [
        'mac_num',
        'assigned',
        'assigned_date',
        'board',
        'uuid',
    ],
    'm1s': [
        'mac_num',
        'assigned',
        'assigned_date',
        'board',
        'uuid',
    ],
}
