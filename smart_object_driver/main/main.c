/* i2c - Example

   For other examples please check:
   https://github.com/espressif/esp-idf/tree/master/examples

   See README.md file to get detailed usage of this example.

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include "wifi.h"
#include "tcp_server.h"
#include "TCS34725.h"
#include "ADXL345.h"
#include "LP5024.h"
#include <math.h>

#include "behaviors.h"
#include "mission1.h"
#include "mission2.h"
#include "mission3.h"


TaskHandle_t xHandle = NULL;
int8_t current_mission = 0;

#define BLINK_GPIO 12

static void respond(const int sock){
        char rgb_string[50];
		int written = tcp_respond(sock, rgb_string, sizeof(rgb_string));
		if (written < 0) {
            ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
        }

}


int char_to_int(char c) {
    int num = 0;
    num = c - '0';
    return num;
}

void clear_task_handle(TaskHandle_t *xHandle, int8_t mission_to_stop) {
    if (*xHandle != NULL) {
        vTaskDelete(*xHandle);
        printf("REMOVE THE TASK \n");
    }
    switch (mission_to_stop) {
        case 1:
            mission1_stop();
            break;
        case 2:
            mission2_stop();
            break;
        case 3:
            mission3_stop();
            break;
        default:
            break;
    }
}


static void do_config_global(int config) {

    char str_config[2];
    memset(str_config, '0', 2);
    sprintf(str_config, "%d", config);
    
    int8_t confs = char_to_int(str_config[0]);
    printf("CONFIGURATION GLOBAL: %d \n", confs);
    switch (confs){
            case 1: ;//mission1_start
                int8_t color_to_display = char_to_int(str_config[1]);
                clear_task_handle(&xHandle, 1);
                current_mission = 1;
                xTaskCreate(mission1_start, "mission1_start_task_0", 1024 * 2, (void *)color_to_display, 7, &xHandle);
                break;
            case 2: //mission2_start
                clear_task_handle(&xHandle, 2);
                current_mission = 2;
                int8_t color_floor = char_to_int(str_config[1]);
                xTaskCreate(mission2_start, "mission2_start_task_0", 1024 * 2, (void *)color_floor, 7, &xHandle);
                break;
            case 3: //mission3_start
                clear_task_handle(&xHandle, 3);
                current_mission = 3;
                xTaskCreate(mission3_start, "mission3_start_task_0", 1024 * 2, (void *)NULL, 7, &xHandle);
                break;
            case 4: ;//stop missions
                printf("CLEAR THE TASK \n");
                clear_task_handle(&xHandle, current_mission);
                break;
            case 5:
                printf("CALIBRATE THE GROUND SENSOR, COLOR WHITE \n");
                xTaskCreate(TCS34725_calibrate, "calibration", 1024 * 2, (void *)0, 7, NULL);
                break;
            case 6:
                printf("CALIBRATE THE GROUND SENSOR, COLOR BLACK \n");
                xTaskCreate(TCS34725_calibrate, "calibration", 1024 * 2, (void *)1, 7, NULL);
                break;
            default:
                printf("DEFAULT \n");
                break;
        }


}


static void test(int config) {
    for (int j=0; j < 24; j ++) {
        LP5024_setColor(j, 0);
    }
    char str_config[50];
    memset(str_config, '0', 50);
    sprintf(str_config, "%d", config);
    
    char pow[4];
    memset(pow, '\0', 4);
    for (int k=0; k<4; k++){
        int offset = 2 + k;
        if (str_config[offset] != '\0'){
            pow[k] = str_config[offset];
        }
    }
    int brightness = atoi(pow);
    int power = 0;
    int channel = 0;
    if(str_config[0] == '1'){
        channel = 0;
    }else if(str_config[0] == '2') {
        channel = 1;
    }
    else if(str_config[0] == '3') {
        channel = 2;
    }


    if(str_config[1] == '1'){
        for (int i=channel; i < 24; i = i + 3) {
            LP5024_setColor(i, brightness);
        }
    }else if(str_config[1] == '2') {
        for (int i= channel; i < 9; i = i + 3) {
            LP5024_setColor(i, brightness);
        }
    }
    else if(str_config[1] == '3') {
        for (int i= channel; i < 12; i = i + 3) {
            LP5024_setColor(i, brightness);
        }
    }


}

static void tcp_server_task(void *pvParameters){
    int listen_sock = tcp_server_init(pvParameters);
	gpio_reset_pin(BLINK_GPIO);
	gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
    if(listen_sock == 1){
		return;
	}
    TaskHandle_t xHandle_ground_sensor = NULL;
    while (1) {
		int sock = tcp_socket_listening(listen_sock); //waiting for the connection (blocking)
		printf("socket %d \n", sock);
        int num = get_action(sock);
        printf("ACTION %d \n", num);
        switch (num){
            case START:
                printf("SMART OBJECT INIT \n");
                smart_object_init();
                break;
            case STOP:
                break;
            case TEST: ;
                int config = get_config(sock);
                test(config);
                printf("TEST: DISPLAY COLOR %d \n", config);
                break;
            case RESTART:
                printf("RESTARTING THE DEVICE! \n");
                fflush(stdout);
                esp_restart();
                break;
            case GLOBAL_CONFIG: ;
                int global_config = get_config(sock);
                do_config_global(global_config);
                break;
            default:
                printf("DEFAULT \n");
                break;
        }
        printf("SHUTDOWN OF THE SOCKET \n");
        shutdown(sock, 0);
        close(sock);
    }
    close(listen_sock);
    vTaskDelete(NULL);
}


void app_main(void){
        //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_LOGI(TAG, "ESP_WIFI_MODE_AP");
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());


   wifi_init_softap();

/*int con = getCon();  //for wifi uncomment this all
while(con == 0){
    vTaskDelay(100/ portTICK_RATE_MS);
    con = getCon();
}*/


#ifdef CONFIG_EXAMPLE_IPV4
    printf("STARTING TCP SERVER \n");
    xTaskCreate(tcp_server_task, "tcp_server", 4096, (void*)AF_INET, 5, NULL);
#endif
#ifdef CONFIG_EXAMPLE_IPV6
    xTaskCreate(tcp_server_task, "tcp_server", 4096, (void*)AF_INET6, 5, NULL);
#endif
   smart_object_init();

   /* 
     float r;
     float g;
     float b;
     TCS34725_get_calibrated_values(0, &r, &g, &b);
     printf("r: %f g: %f b: %f\n", r, g, b);
     TCS34725_get_calibrated_values(1, &r, &g, &b);
     printf("r: %f g: %f b: %f\n", r, g, b);*/
}
