#include "iGraphics.h"

#include <stdio.h>

#include <string.h>

int x = 300, y = 300, r = 20;
int condition = 0;
char input[1000];
char input2[1000];
char input3[1000];
char tmp[1000];
int xpos1 = -600;
int xpos2 = -600;
int xpos3 = -600;
int xpos4 = -600;
int xpos5 = -600;
int xpos6 = -600;
int xpos7 = -600;
int xpos8 = -600;
int xpos9 = -600;
int xpos10 = -600;
int xpos11 = -600;
int xpos12 = -600;
int xpos13 = -600;
int xpos14 = -600;
int xpos15 = -600;
int xpos16 = -600;
int xpos17 = -600;
int task;
int glob_counter;
struct obostha {
  int obosthas;
  int coordinate;
};

struct obostha obostha[50];
int values[25] = {
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1
};

char tmp2[1000];
char tmp3[1000];
int deadline_tracker = 0;

int local_hour() {
  time_t t = time(NULL);
  struct tm tm = * localtime( & t);
  //printf("now:%02d:%02d:%02d\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
  return tm.tm_hour;
}
int local_minute() {
  time_t t = time(NULL);
  struct tm tm = * localtime( & t);
  //printf("now:%02d:%02d:%02d\n",tm.tm_hour, tm.tm_min, tm.tm_sec);
  return tm.tm_min;
}

struct deadline {
  int hour;
  int minute;
};

struct deadline dedline[1000];

void read_deadline_file(void) {
  FILE * f = fopen("deadline.txt", "r");
  deadline_tracker = 0;
  if (f != NULL) {
    char x, y, z, m;
    while (fscanf(f, "%c%c %c%c,", & z, & x, & y, & m) == 4) {
      if (z != '0') {
        dedline[deadline_tracker].hour = (x - '0') + (z - '0') * 10;
      } else if (z == '0') {
        dedline[deadline_tracker].hour = x - '0';
      }
      if (y != '0') {
        dedline[deadline_tracker].minute = (m - '0') + (y - '0') * 10;

      } else if (y == '0') {
        dedline[deadline_tracker].minute = m - '0';
      }

      deadline_tracker++;
    }
  }
  fclose(f);

}

void Add_deadline_minutes(void) {
  FILE * f = fopen("deadline.txt", "a");
  fprintf(f, "%s,", tmp3);
  fclose(f);
  //printf("%s ", tmp3);
  //read_deadline_file();
  condition = 0;
}

void Add_deadline(void) {
  condition = 2;
  FILE * f = fopen("deadline.txt", "a");
  fprintf(f, "%s ", tmp2);
  //condition = 0;
  fclose(f);
  condition = 3;
}

int time_diff(int current_time, int deadline) {
  int time_diff = deadline - current_time;
  return time_diff;
}

void read_task_file(void) {
  FILE * f = fopen("task.txt", "r");
  if (f != NULL) {
    char ntask[100];
    fgets(ntask, 100, f);
    task = ntask[0] - '0';
    printf("task: %i\n", task);
    fclose(f);
  } else {
    task = 1;
  }
}

void show_time(void) {
  FILE * file;
  file = fopen("deadline.txt", "r");
  char x, y, z, m;
  int yaxis = 500;
  while (fscanf(file, "%c%c %c%c,", & z, & x, & y, & m) == 4) {
    char * bufferr;
    bufferr = (char * ) calloc(5, sizeof(char));
    bufferr[0] = z;
    bufferr[1] = x;
    bufferr[2] = ' ';
    bufferr[3] = y;
    bufferr[4] = m;
    iText(598, yaxis, bufferr);
    yaxis -= 30;
    free(bufferr);
  }
  fclose(file);
}

void show_file(void) {
  int counter = 0;
  FILE * file = fopen("to-do list.txt", "r");
  if (file == NULL) {
    printf("Error opening file.\n");
    return;
  }

  char line[100];
  int y = 500;
  while (fgets(line, sizeof(line), file)) {
    char * token = strtok(line, ",");
    while (token != NULL) {
      obostha[counter].coordinate = y;
      if (obostha[counter].obosthas == 1) {
        iRectangle(479, y - 3, 15, 15);
      }
      if (obostha[counter].obosthas == -1) {
        iSetColor(255, 0, 0);
        iFilledRectangle(470, y, 15, 15);
      }
      //printf("%s\n", token);
      iText(500, y, token);
      y -= 30;
      token = strtok(NULL, ",");
      counter++;
    }

  }

  fclose(file);
}

void Add_task(void) {
  FILE * file;
  char str[20];
  sprintf(str, "%d", task);
  file = fopen("to-do list.txt", "a");
  fprintf(file, "%s. %s,", str, tmp);
  task++;
  char str2[20];
  sprintf(str2, "%d", task);
  FILE * f = fopen("task.txt", "w");
  fprintf(f, str2);
  fclose(f);
  fclose(file);
  condition = 2;
}

void draw_prompt(void) {
  iSetColor(255, 0, 0);
  iFilledRectangle(600, 300, 100, 50);
  iSetColor(255, 255, 255);
  iFilledRectangle(600, 300, 20, 10);
}

int hour_remain(int deadline) {
  int a = local_hour();
  return time_diff(a, deadline);
}

int minute_remain(int deadline) {
  int a = local_minute();
  return time_diff(a, deadline);
}

show_remaining_time() {
  int y = 500;
  for (int i = 0; i < deadline_tracker; i++) {
    if (hour_remain(dedline[i].hour) > 0) {
        if(minute_remain(dedline[i].minute)>0)
        {
            char buffer[100];
            sprintf(buffer, "%d", hour_remain(dedline[i].hour));
            iText(680, y, buffer);
            iText(700, y, "hr");
            char bufferr[100];
            sprintf(bufferr,"%d",minute_remain(dedline[i].minute));
            iText(720,y,bufferr);
            iText(750,y,"min");
            y -= 30;
        }
        else if(minute_remain(dedline[i].minute)<0)
        {
            char buffer[100];
            int hour = (hour_remain(dedline[i].hour)*60+minute_remain(dedline[i].minute))/60;
            sprintf(buffer,"%d",hour);
            iText(680, y, buffer);
            iText(700, y, "hr");
            char bufferr[100];
            sprintf(bufferr,"%d",-1*minute_remain(dedline[i].minute));
            iText(720,y,bufferr);
            iText(750,y,"min");
            y -= 30;
        }
    }

    else if(hour_remain(dedline[i].hour)<=0)
    {
      if(minute_remain(dedline[i].minute)<=0)
      {
          iText(680, y, "Time Over");
          y -= 30;
      }
      else if(hour_remain(dedline[i].hour)==0){
            iText(680, y, "0");
            iText(700, y, "hr");
            char bufferr[100];
            sprintf(bufferr,"%d",minute_remain(dedline[i].minute));
            iText(720,y,bufferr);
            iText(750,y,"min");
            y -= 30;

      }


    }

  }
}

void iDraw() {
  iClear();
  iSetColor(151, 234, 84);
  iFilledRectangle(0, 0, 1200, 600);
  iSetColor(3, 169, 244);
  iFilledRectangle(787, 0, 1200, 600);
  iSetColor(0, 0, 0);
  iFilledRectangle(786, 534, 500, 64);
  iSetColor(147, 47, 81);
  iFilledRectangle(786, 317, 600, 217);
  iSetColor(108, 44, 147);
  iFilledRectangle(0, 0, 475, 600);
  iSetColor(216, 145, 28);
  iFilledRectangle(476, 532, 314, 74);
  iSetColor(0, 0, 0);
  iRectangle(472, 532, 103, 68);
  iRectangle(575, 532, 103, 68);
  iRectangle(678, 532, 111, 68);
  iSetColor(0, 0, 255);
  iFilledCircle(1130, 50, 40);
  iSetColor(235, 229, 52);
  iFilledRectangle(130,58,216,43);
  iFilledRectangle(130,111,216,43);
  iFilledRectangle(130,164,216,43);
  iSetColor(0, 0, 0);
  iText(591, 569, "DEADLINE", GLUT_BITMAP_TIMES_ROMAN_10);
  iText(691, 569, "TIME REMAINING", GLUT_BITMAP_TIMES_ROMAN_10);
  iText(501, 569, "TASK", GLUT_BITMAP_TIMES_ROMAN_10);
  iSetColor(255, 235, 59);
  iText(838, 429, input, GLUT_BITMAP_TIMES_ROMAN_24);
  iText(838, 429, input2, GLUT_BITMAP_TIMES_ROMAN_24);
  iText(838, 429, input3, GLUT_BITMAP_TIMES_ROMAN_24);
  iSetColor(0, 0, 0);
  iText(1105, 45, "ADD", GLUT_BITMAP_TIMES_ROMAN_24);
  iSetColor(255, 0, 0);
  FILE * fp;
  char cmp;
  fp = fopen("tick1.txt","r");
  fscanf(fp, "%c", & cmp);
  if (cmp == '1') {
    iShowBMP2(455,484,"tick_box.bmp",0xffffff);
  }
  fclose(fp);

  cmp = '0';
  fp = fopen("tick2.txt","r");
  fscanf(fp, "%c", & cmp);
  if (cmp == '1') {
    iShowBMP2(455,484-30,"tick_box.bmp",0xffffff);
  }
  fclose(fp);
  cmp = '0';

  fp = fopen("tick3.txt","r");
  fscanf(fp, "%c", & cmp);
  if (cmp == '1') {
    iShowBMP2(455,484-60,"tick_box.bmp",0xffffff);
  }
  fclose(fp);
  cmp = '0';

  fp = fopen("tick4.txt","r");
  fscanf(fp, "%c", & cmp);
  if (cmp == '1') {
    iShowBMP2(455,484-90,"tick_box.bmp",0xffffff);
  }
  fclose(fp);
  cmp = '0';

  fp = fopen("tick5.txt","r");
  fscanf(fp, "%c", & cmp);
  if (cmp == '1') {
    iShowBMP2(455,484-120,"tick_box.bmp",0xffffff);
  }
  fclose(fp);
  cmp = '0';

  fp = fopen("tick6.txt","r");
  fscanf(fp, "%c", & cmp);
  if (cmp == '1') {
    iShowBMP2(455,484-150,"tick_box.bmp",0xffffff);
  }
  fclose(fp);
  cmp = '0';

  fp = fopen("tick7.txt","r");
  fscanf(fp, "%c", & cmp);
  if (cmp == '1') {
    iShowBMP2(455,484-180,"tick_box.bmp",0xffffff);
  }
  fclose(fp);
  cmp = '0';

  fp = fopen("tick8.txt","r");
  fscanf(fp, "%c", & cmp);
  if (cmp == '1') {
    iShowBMP2(455,484-210,"tick_box.bmp",0xffffff);
  }
  fclose(fp);
  cmp = '0';

  fp = fopen("tick9.txt","r");
  fscanf(fp, "%c", & cmp);
  if (cmp == '1') {
    iShowBMP2(455,484-240,"tick_box.bmp",0xffffff);
  }
  fclose(fp);
  cmp = '0';

  fp = fopen("tick10.txt","r");
  fscanf(fp, "%c", & cmp);
  if (cmp == '1') {
    iShowBMP2(455,484-270,"tick_box.bmp",0xffffff);
  }
  fclose(fp);
  cmp = '0';

  fp = fopen("tick11.txt","r");
  fscanf(fp, "%c", & cmp);
  if (cmp == '1') {
    iShowBMP2(455,484-300,"tick_box.bmp",0xffffff);
  }
  fclose(fp);
  cmp = '0';

  fp = fopen("tick12.txt","r");
  fscanf(fp, "%c", & cmp);
  if (cmp == '1') {
    iShowBMP2(455,484-330,"tick_box.bmp",0xffffff);
  }
  fclose(fp);
  cmp = '0';

  fp = fopen("tick13.txt","r");
  fscanf(fp, "%c", & cmp);
  if (cmp == '1') {
    iShowBMP2(455,484-360,"tick_box.bmp",0xffffff);
  }
  fclose(fp);
  cmp = '0';

  fp = fopen("tick14.txt","r");
  fscanf(fp, "%c", & cmp);
  if (cmp == '1') {
    iShowBMP2(455,484-390,"tick_box.bmp",0xffffff);
  }
  fclose(fp);
  cmp = '0';

  fp = fopen("tick15.txt","r");
  fscanf(fp, "%c", & cmp);
  if (cmp == '1') {
    iShowBMP2(455,484-420,"tick_box.bmp",0xffffff);
  }
  fclose(fp);
  cmp = '0';

  fp = fopen("tick16.txt","r");
  fscanf(fp, "%c", & cmp);
  if (cmp == '1') {
    iShowBMP2(455,484-450,"tick_box.bmp",0xffffff);
  }
  fclose(fp);
  cmp = '0';

  fp = fopen("tick17.txt","r");
  fscanf(fp, "%c", & cmp);
  if (cmp == '1') {
    iShowBMP2(455,484-480,"tick_box.bmp",0xffffff);
  }
  fclose(fp);
  cmp = '0';

  /*iFilledCircle(xpos1, 87, 5);
  iFilledCircle(xpos3, 477, 5);
  iFilledCircle(xpos4, 446, 5);
  iFilledCircle(xpos5, 418, 5);
  iFilledCircle(xpos6, 386, 5);
  iFilledCircle(xpos7, 357, 5);
  iFilledCircle(xpos8, 326, 5);
  iFilledCircle(xpos9, 297, 5);
  iFilledCircle(xpos10, 267, 5);
  iFilledCircle(xpos11, 235, 5);
  iFilledCircle(xpos12, 206, 5);
  iFilledCircle(xpos13, 177, 5);
  iFilledCircle(xpos14, 147, 5);
  iFilledCircle(xpos15, 117, 5);
  iFilledCircle(xpos16, 57, 5);
  iFilledCircle(xpos17, 28, 5);*/
  iSetColor(0, 0, 0);
  char task_str[20];
  sprintf(task_str, "%d", task);
  //char deadline_str[20];
  //sprintf(deadline_str, "%d", dedline[deadline_tracker].hour);
  //iText(10, 590,deadline_str, GLUT_BITMAP_TIMES_ROMAN_10);
  iText(10, 560, task_str, GLUT_BITMAP_TIMES_ROMAN_10);
  show_file();
  show_time();
  read_deadline_file();
  show_remaining_time();
  iText(882,183,"DAILY TO-DO LIST",GLUT_BITMAP_TIMES_ROMAN_24);
  iText(175,70,"CLEAR FILES",GLUT_BITMAP_HELVETICA_18);
  iText(163,70+53,"WEEKLY TO-DO",GLUT_BITMAP_HELVETICA_18);
  iText(153,70+53+53,"MONTHLY TO-DO",GLUT_BITMAP_HELVETICA_18);
  if (condition == 0) {
    iSetColor(255, 255, 255);
    iText(890, 561, "Typing Console ", GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(0, 0, 0);
  }
  if (condition == 1) {
    iSetColor(255, 255, 255);
    iText(890, 561, "Add Task ", GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(0, 0, 0);
  }
  if (condition == 2) {
    iSetColor(255, 255, 255);
    iText(890, 561, "Add deadline hour ", GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(0, 0, 0);
  }
  if (condition == 3) {
    iSetColor(255, 255, 255);
    iText(884, 561, "Add deadline minutes: ", GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(0, 0, 0);
  }
}

void iMouseMove(int mx, int my) {
  printf("x = %d, y= %d\n", mx, my);
}

void iMouse(int button, int state, int mx, int my) {
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    if (mx >= 1010 && mx <= 1190 && my >= 10 && my <= 90) {
      condition = 1;
    } else if (mx >= 550 && mx <= 650 && my >= 250 && my <= 350 && condition == 1) {
      strcpy(tmp, input);
      Add_task();
      condition = 0;
    } else if (mx >= 480 && mx <= 505 && my >= 0 && my <= 600) {

      if (my >= 90 - 5 && my <= 90 + 5) {
        FILE * fp;
        //fp = fopen("tick15.txt","r");
        //int buff;
        //fscanf(fp,"%d",&buff);
        //int a = buff;
        //a = a*(-1);
        //char x[20];
        //sprintf(x,"%d",a);
        //fclose(fp);
        fp = fopen("tick15.txt", "w");
        fprintf(fp, "1");
        fclose(fp);
        printf("%i %i %i xpos1\n", mx, my, xpos1);
      } else if (my >= 508 - 10 && my <= 508 + 10) {
        FILE * fp;
        fp = fopen("tick1.txt", "w");
        fprintf(fp, "1");
        fclose(fp);
        printf("%i %i %i xpos2\n", mx, my, xpos2);
      } else if (my >= 477 - 10 && my <= 477 + 10) {
        FILE * fp;
        fp = fopen("tick2.txt", "w");
        fprintf(fp, "1");
        fclose(fp);
        printf("%i %i %i xpos3\n", mx, my, xpos3);
      } else if (my >= 440 - 10 && my <= 440 + 10) {
        FILE * fp;
        fp = fopen("tick3.txt", "w");
        fprintf(fp, "1");
        fclose(fp);
        printf("%i %i %i xpos4\n", mx, my, xpos4);
      } else if (my >= 410 - 10 && my <= 410 + 10) {
        FILE * fp;
        fp = fopen("tick4.txt", "w");
        fprintf(fp, "1");
        fclose(fp);
        printf("%i %i %i xpos5\n", mx, my, xpos5);
      } else if (my >= 380 - 10 && my <= 380 + 10) {
        FILE * fp;
        fp = fopen("tick5.txt", "w");
        fprintf(fp, "1");
        fclose(fp);
        printf("%i %i %i xpos6\n", mx, my, xpos6);
      } else if (my >= 350 - 10 && my <= 350 + 10) {
        FILE * fp;
        fp = fopen("tick6.txt", "w");
        fprintf(fp, "1");
        fclose(fp);
        printf("%i %i %i xpos7\n", mx, my, xpos7);
      } else if (my >= 320 - 10 && my <= 320 + 10) {
        FILE * fp;
        fp = fopen("tick7.txt", "w");
        fprintf(fp, "1");
        fclose(fp);
        printf("%i %i %i xpos8\n", mx, my, xpos8);
      } else if (my >= 290 - 10 && my <= 290 + 10) {
        FILE * fp;
        fp = fopen("tick8.txt", "w");
        fprintf(fp, "1");
        fclose(fp);
        printf("%i %i %i xpos9\n", mx, my, xpos9);
      } else if (my >= 260 - 10 && my <= 260 + 10) {
        FILE * fp;
        fp = fopen("tick9.txt", "w");
        fprintf(fp, "1");
        fclose(fp);
        printf("%i %i %i xpos10\n", mx, my, xpos10);
      } else if (my >= 230 - 10 && my <= 230 + 10) {
        FILE * fp;
        fp = fopen("tick10.txt", "w");
        fprintf(fp, "1");
        fclose(fp);
        xpos11 = 487;
        printf("%i %i %i xpos11\n", mx, my, xpos1);
      } else if (my >= 200 - 10 && my <= 200 + 10) {
        FILE * fp;
        fp = fopen("tick11.txt", "w");
        fprintf(fp, "1");
        fclose(fp);
        printf("%i %i %i xpos12\n", mx, my, xpos12);
      } else if (my >= 170 - 10 && my <= 170 + 10) {
        FILE * fp;
        fp = fopen("tick12.txt", "w");
        fprintf(fp, "1");
        fclose(fp);
        printf("%i %i %i xpos13\n", mx, my, xpos13);
      } else if (my >= 140 - 10 && my <= 140 + 10) {
        FILE * fp;
        fp = fopen("tick13.txt", "w");
        fprintf(fp, "1");
        fclose(fp);
        printf("%i %i %i xpos14\n", mx, my, xpos14);
      } else if (my >= 110 - 10 && my <= 110 + 10) {
        FILE * fp;
        fp = fopen("tick14.txt", "w");
        fprintf(fp, "1");
        fclose(fp);
        printf("%i %i %i xpos15\n", mx, my, xpos15);
      } else if (my >= 50 - 10 && my <= 50 + 10) {
        FILE * fp;
        fp = fopen("tick16.txt", "w");
        fprintf(fp, "1");
        fclose(fp);
        printf("%i %i %i xpos16\n", mx, my, xpos16);
      } else if (my >= 20 - 10 && my <= 20 + 10) {
        FILE * fp;
        fp = fopen("tick17.txt", "w");
        fprintf(fp, "1");
        fclose(fp);
        printf("%i %i %i xpos17\n", mx, my, xpos17);
      }
    }
    else if(mx>=130 && mx<=347 && my>=57 && my<=101)
    {
        FILE *fp;
        fp=fopen("deadline.txt","w");
        fclose(fp);
        fp=fopen("to-do list.txt","w");
        fclose(fp);
        fp=fopen("task.txt","w");
        fprintf(fp,"1");
        fclose(fp);
        fp=fopen("tick17.txt","w");
        fclose(fp);
                fp=fopen("tick1.txt","w");
        fclose(fp);
                fp=fopen("tick2.txt","w");
        fclose(fp);
                fp=fopen("tick3.txt","w");
        fclose(fp);
                fp=fopen("tick4.txt","w");
        fclose(fp);
                fp=fopen("tick5.txt","w");
        fclose(fp);
                fp=fopen("tick6.txt","w");
        fclose(fp);
                fp=fopen("tick7.txt","w");
        fclose(fp);
                fp=fopen("tick8.txt","w");
        fclose(fp);
                fp=fopen("tick9.txt","w");
        fclose(fp);
                fp=fopen("tick10.txt","w");
        fclose(fp);
                fp=fopen("tick11.txt","w");
        fclose(fp);
                fp=fopen("tick12.txt","w");
        fclose(fp);
                fp=fopen("tick13.txt","w");
        fclose(fp);
                fp=fopen("tick14.txt","w");
        fclose(fp);
                fp=fopen("tick15.txt","w");
        fclose(fp);
                fp=fopen("tick16.txt","w");
        fclose(fp);
    }
  }
}

void iKeyboard(unsigned char key) {
  if (key == '\r' && condition == 1) {
    // '\r' is the ASCII code for the Enter key
    // Do something with the input
    iSetColor(255, 0, 0);
    strcpy(tmp, input);
    Add_task();
    // Clear the input string
    memset(input, 0, sizeof(input));
  } else if (condition == 1 && key != '\r') {
    // Add the typed character to the input string
    int len = strlen(input);
    if (len < sizeof(input) - 1) {
      input[len] = key;
      input[len + 1] = '\0';
    }
  } else if (condition == 2 && key != '\r') {
    int len = strlen(input2);
    if (len < sizeof(input2) - 1) {
      input2[len] = key;
      input2[len + 1] = '\0';
    }
  } else if (key == '\r' && condition == 2) { // '\r' is the ASCII code for the Enter key
    // Do something with the input
    iSetColor(255, 0, 0);
    strcpy(tmp2, input2);
    Add_deadline();
    memset(input2, 0, sizeof(input2));
    // Clear the input string
  } else if (condition == 3 && key != '\r') {
    int len = strlen(input3);
    if (len < sizeof(input3) - 1) {
      input3[len] = key;
      input3[len + 1] = '\0';
    }
  } else if (key == '\r' && condition == 3) { // '\r' is the ASCII code for the Enter key
    // Do something with the input
    iSetColor(255, 0, 0);
    strcpy(tmp3, input3);
    Add_deadline_minutes();
    // Clear the input string
    memset(input3, 0, sizeof(input3));
  }
}

void iSpecialKeyboard(unsigned char key) {
  // Nothing here yet
}

int main() {
  for (int i = 0; i < 25; i++) {

    obostha[i].obosthas = values[i];
  }
  read_task_file();
  iInitialize(1200, 600, "fml");
  return 0;
}