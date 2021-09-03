#include "mission1.h"
#include "behaviors.h"



int8_t steps_mission1 = 20;

int8_t mission1_get_random_color() {
    return esp_random() % 3;
}

void mission1_start(void *_color_to_display) {
    float alpha = 0.5;
    int8_t color_to_display = (int8_t) _color_to_display;
    printf("COLOR TO DISPLAY: %d \n",color_to_display);
    if (color_to_display == 3) { //use random color
        color_to_display = mission1_get_random_color();
    }
    int16_t x, mean_x;
    int16_t y, mean_y;
    int16_t z, mean_z;
    
    mean_x = 0;
    mean_y = 0;
    mission1_sample(&mean_x, &mean_y);
    printf("MEAN VALUES: X value: %d, Y value: %d \n", mean_x, mean_y);

    int16_t moving[20];
    display_color_behavior(color_to_display, 0);
    int16_t offset = 5;
    int steps = steps_mission1;
    m_movingState = STATIONNARY;
    while (true) {
        for (int k=0; k<20; k++) {
            moving[k] = 0;
        }
        ADXL345_get_data(&x, &y, &z);
       // printf("X value: %d , Y value: %d, Z value: %d \n",  x, y, z);
        if ((x < mean_x - offset || x > mean_x + offset) || ((y < mean_y - offset || y > mean_y + offset))) {
            moving[steps_mission1] = 1;
        } else {
            moving[steps_mission1] = 0;
        }
        switch (m_movingState) {
            case STATIONNARY:
                if ((x < mean_x - offset || x > mean_x + offset) || ((y < mean_y - offset || y > mean_y + offset))) {
                    m_movingState = MOVING;
                    color_to_display++;
                    if (color_to_display == 3) {
                        color_to_display = 0;
                    }
                    display_color_behavior(color_to_display, 0);
                }
                break;
            case MOVING:
                steps_mission1--;
                if ((x < mean_x - offset || x > mean_x + offset) || ((y < mean_y - offset || y > mean_y + offset))) {
                    moving[steps_mission1] = 1;
                } else {
                    moving[steps_mission1] = 0;
                }
                if(steps_mission1 == 0) {
                    steps_mission1 = steps;
                    int sum = 0;
                    for (int i=0; i<steps; i++) {
                        sum = sum + moving[i];
                    }
                    printf("SUM: %d \n",sum);
                    if (sum > 4) {
                        color_to_display++;
                        if (color_to_display == 3) {
                            color_to_display = 0;
                        }
                        display_color_behavior(color_to_display, 0);
                        m_movingState = MOVING;
                    } else {
                        m_movingState = STATIONNARY;
                        printf("OBJECT IS STATIONARY! \n");
                    }
                }

                break;
            default:
                break;
        }

       /* for (int j=0; j< steps; j++) {
                printf("VALUE %d \n", moving[j]);
        }*/

        if(steps_mission1 == 0) {
            steps_mission1 = steps;
            int sum = 0;
            for (int i=0; i<steps; i++) {
                sum = sum + moving[i];
            }
            printf("SUM: %d \n",sum);
            if (sum > 4) {
                color_to_display++;
                if (color_to_display == 3) {
                    color_to_display = 0;
                }
                display_color_behavior(color_to_display, 0);
                printf("OBJECT IS MOVING! \n");
            } else {
                printf("OBJECT IS STATIONARY! \n");
            }
        }
         vTaskDelay(100/ portTICK_RATE_MS);
        
    }
}

void mission1_sample(int16_t *mean_x, int16_t *mean_y) {
    int16_t sample_x[100];
    int16_t sample_y[100];
    int16_t x,y,z;
    int i = 0;
    while(i < 100) {
        ADXL345_get_data(&x, &y, &z);
        sample_x[i] = x;
        sample_y[i] = y;
        printf("sampling \n");
        vTaskDelay(100/ portTICK_RATE_MS);
        i++;
    } 
    for (int j=0; j < 100; j++) {
        *mean_x = *mean_x + sample_x[j];
        *mean_y = *mean_y + sample_y[j];
    }
    *mean_x = *mean_x/100;
    *mean_y = *mean_y/100;
}


void mission1_stop() {
    display_none();
    printf("MISSION STOPPED \n");
}