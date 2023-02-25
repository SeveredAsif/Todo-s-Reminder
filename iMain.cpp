#include "iGraphics.h"

#include <stdio.h>

#include <string.h>

int x = 300, y = 300, r = 20;
int condition = 0;
char input[1000];
char input2[1000];
char input3[1000];
char tmp[1000];
int task;

char tmp2[1000];
char tmp3[1000];
int deadline_tracker = 0;

int local_hour() {
  time_t t = time(NULL);
  struct tm tm = * localtime( & t);
  //printf("now:%02d:%02d:%02d\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
  return tm.tm_hour;
}

int local_day() {
  time_t t = time(NULL);
  struct tm tm = * localtime( & t);
  //printf("now:%02d:%02d:%02d\n",tm.tm_hour, tm.tm_min, tm.tm_sec);
  return tm.tm_wday;
}

int local_minute() {
  time_t t = time(NULL);
  struct tm tm = * localtime( & t);
  //printf("now:%02d:%02d:%02d\n",tm.tm_hour, tm.tm_min, tm.tm_sec);
  return tm.tm_min;
}
int local_second() {
  time_t t = time(NULL);
  struct tm tm = * localtime( & t);
  //printf("now:%02d:%02d:%02d\n",tm.tm_hour, tm.tm_min, tm.tm_sec);
  return tm.tm_sec;
}

struct deadline {
  int hour;
  int minute;
  int day;
};

struct deadline dedline[1000];

void read_deadline_file(void) {
  FILE * f = fopen("deadline_week.txt", "r");
  deadline_tracker = 0;
  if (f != NULL) {
    char x, y, z, m;
    while (fscanf(f, "%c,", & z) == 1) {
      dedline[deadline_tracker].day = z - '0';
      deadline_tracker++;
    }
  }
  fclose(f);

}

void Add_deadline(void) {
  condition = 2;
  FILE * f = fopen("deadline_week.txt", "a");
  FILE * fp = fopen("deadline_string.txt", "a");
  if (strcmp(tmp2, "Monday") == 0 || strcmp(tmp2, "monday") == 0) {
    fprintf(f, "1,");
    fclose(f);
    fprintf(fp, "%s,", tmp2);
    fclose(fp);
    condition = 0;
  } else if (strcmp(tmp2, "Sunday") == 0 || strcmp(tmp2, "sunday") == 0) {
    fprintf(f, "0,");
    fclose(f);
    fprintf(fp, "%s,", tmp2);
    fclose(fp);
    condition = 0;
  } else if (strcmp(tmp2, "Tuesday") == 0 || strcmp(tmp2, "tuesday") == 0) {
    fprintf(f, "2,");
    fclose(f);
    fprintf(fp, "%s,", tmp2);
    fclose(fp);
    condition = 0;
  } else if (strcmp(tmp2, "Wednesday") == 0 || strcmp(tmp2, "wednesday") == 0) {
    fprintf(f, "3,");
    fclose(f);
    fprintf(fp, "%s,", tmp2);
    fclose(fp);
    condition = 0;
  } else if (strcmp(tmp2, "Thursday") == 0 || strcmp(tmp2, "thursday") == 0) {
    fprintf(f, "4,");
    fclose(f);
    fprintf(fp, "%s,", tmp2);
    fclose(fp);
    condition = 0;
  } else if (strcmp(tmp2, "Friday") == 0 || strcmp(tmp2, "friday") == 0) {
    fprintf(f, "5,");
    fclose(f);
    fprintf(fp, "%s,", tmp2);
    fclose(fp);
    condition = 0;
  } else if (strcmp(tmp2, "Saturday") == 0 || strcmp(tmp2, "saturday") == 0) {
    fprintf(f, "6,");
    fclose(f);
    fprintf(fp, "%s,", tmp2);
    fclose(fp);
    condition = 0;
  } else {
    fclose(f);
    fclose(fp);
  }

}

int time_diff(int current_time, int deadline) {
  int time_diff = deadline - current_time;
  return time_diff;
}

void read_task_file_week(void) {
  FILE * f = fopen("task_week.txt", "r");
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
  file = fopen("deadline_string.txt", "r");
  char line[100];
  int y = 500;
  while (fgets(line, sizeof(line), file)) {
    char * token = strtok(line, ",");
    while (token != NULL) {
      iText(598, y, token);
      y -= 30;
      token = strtok(NULL, ",");
    }
    fclose(file);

  }
}

void show_file(void) {
  int counter = 0;
  FILE * file = fopen("to-do list_week.txt", "r");
  if (file == NULL) {
    printf("Error opening file.\n");
    return;
  }

  char line[100];
  int y = 500;
  while (fgets(line, sizeof(line), file)) {
    char * token = strtok(line, ",");
    while (token != NULL) {
      iRectangle(479, y - 3, 15, 15);
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
  file = fopen("to-do list_week.txt", "a");
  fprintf(file, "%s. %s,", str, tmp);
  task++;
  char str2[20];
  sprintf(str2, "%d", task);
  FILE * f = fopen("task_week.txt", "w");
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
int day_remain(int deadline) {
  int a = local_day();
  return time_diff(a, deadline);
}

int minute_remain(int deadline) {
  int a = local_minute();
  return time_diff(a, deadline);
}

show_remaining_time() {
  int y = 500;
  for (int i = 0; i < deadline_tracker; i++) {
    //printf("%i day\n",day_remain(dedline[i].day));
    //printf("%i local day\n",local_day());
    if (day_remain(dedline[i].day) >= 0) {
      char buffer[100];
      sprintf(buffer, "%d", day_remain(dedline[i].day) + 1);
      iText(680, y, buffer);
      y -= 30;

    } else {
      iText(680, y, "Time Over");
      y -= 30;

    }

  }
}

void iDraw() {
  iClear();
  read_task_file_week();
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
  iSetColor(0, 0, 0);
  iFilledRectangle(130, 561 - 60, 216, 60);
  //154,522
  iSetColor(255, 0, 0);
  char tmp[20];
  int hour = local_hour();
  int minute = local_minute();
  int second = local_second();
  sprintf(tmp, "%d", hour);
  iText(154 + 30 + 10, 522, tmp, GLUT_BITMAP_TIMES_ROMAN_24);
  iText(154 + 30 + 10 + 25, 522, ":", GLUT_BITMAP_TIMES_ROMAN_24);
  sprintf(tmp, "%d", minute);
  iText(154 + 30 + 30 + 10, 522, tmp, GLUT_BITMAP_TIMES_ROMAN_24);
  iText(154 + 30 + 30 + 10 + 25, 522, ":", GLUT_BITMAP_TIMES_ROMAN_24);
  sprintf(tmp, "%d", second);
  iText(154 + 30 + 30 + 30 + 10, 522, tmp, GLUT_BITMAP_TIMES_ROMAN_24);
  iSetColor(235, 229, 52);
  iFilledRectangle(130, 58, 216, 43);
  iFilledRectangle(130, 111, 216, 43);
  iFilledRectangle(130, 164, 216, 43);
  iSetColor(0, 0, 0);
  iText(591, 569, "DEADLINE", GLUT_BITMAP_TIMES_ROMAN_10);
  iText(691, 569, "DAY REMAINING", GLUT_BITMAP_TIMES_ROMAN_10);
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
  fp = fopen("tick1_week.txt", "r");
  fscanf(fp, "%c", & cmp);
  if (cmp == '1') {
    iShowBMP2(455, 484, "tick_box.bmp", 0xffffff);
  }
  fclose(fp);

  cmp = '0';
  fp = fopen("tick2_week.txt", "r");
  fscanf(fp, "%c", & cmp);
  if (cmp == '1') {
    iShowBMP2(455, 484 - 30, "tick_box.bmp", 0xffffff);
  }
  fclose(fp);
  cmp = '0';

  fp = fopen("tick3_week.txt", "r");
  fscanf(fp, "%c", & cmp);
  if (cmp == '1') {
    iShowBMP2(455, 484 - 60, "tick_box.bmp", 0xffffff);
  }
  fclose(fp);
  cmp = '0';

  fp = fopen("tick4_week.txt", "r");
  fscanf(fp, "%c", & cmp);
  if (cmp == '1') {
    iShowBMP2(455, 484 - 90, "tick_box.bmp", 0xffffff);
  }
  fclose(fp);
  cmp = '0';

  fp = fopen("tick5_week.txt", "r");
  fscanf(fp, "%c", & cmp);
  if (cmp == '1') {
    iShowBMP2(455, 484 - 120, "tick_box.bmp", 0xffffff);
  }
  fclose(fp);
  cmp = '0';

  fp = fopen("tick6_week.txt", "r");
  fscanf(fp, "%c", & cmp);
  if (cmp == '1') {
    iShowBMP2(455, 484 - 150, "tick_box.bmp", 0xffffff);
  }
  fclose(fp);
  cmp = '0';

  fp = fopen("tick7_week.txt", "r");
  fscanf(fp, "%c", & cmp);
  if (cmp == '1') {
    iShowBMP2(455, 484 - 180, "tick_box.bmp", 0xffffff);
  }
  fclose(fp);
  cmp = '0';

  fp = fopen("tick8_week.txt", "r");
  fscanf(fp, "%c", & cmp);
  if (cmp == '1') {
    iShowBMP2(455, 484 - 210, "tick_box.bmp", 0xffffff);
  }
  fclose(fp);
  cmp = '0';

  fp = fopen("tick9_week.txt", "r");
  fscanf(fp, "%c", & cmp);
  if (cmp == '1') {
    iShowBMP2(455, 484 - 240, "tick_box.bmp", 0xffffff);
  }
  fclose(fp);
  cmp = '0';

  fp = fopen("tick10_week.txt", "r");
  fscanf(fp, "%c", & cmp);
  if (cmp == '1') {
    iShowBMP2(455, 484 - 270, "tick_box.bmp", 0xffffff);
  }
  fclose(fp);
  cmp = '0';

  fp = fopen("tick11_week.txt", "r");
  fscanf(fp, "%c", & cmp);
  if (cmp == '1') {
    iShowBMP2(455, 484 - 300, "tick_box.bmp", 0xffffff);
  }
  fclose(fp);
  cmp = '0';

  fp = fopen("tick12_week.txt", "r");
  fscanf(fp, "%c", & cmp);
  if (cmp == '1') {
    iShowBMP2(455, 484 - 330, "tick_box.bmp", 0xffffff);
  }
  fclose(fp);
  cmp = '0';

  fp = fopen("tick13_week.txt", "r");
  fscanf(fp, "%c", & cmp);
  if (cmp == '1') {
    iShowBMP2(455, 484 - 360, "tick_box.bmp", 0xffffff);
  }
  fclose(fp);
  cmp = '0';

  fp = fopen("tick14_week.txt", "r");
  fscanf(fp, "%c", & cmp);
  if (cmp == '1') {
    iShowBMP2(455, 484 - 390, "tick_box.bmp", 0xffffff);
  }
  fclose(fp);
  cmp = '0';

  fp = fopen("tick15_week.txt", "r");
  fscanf(fp, "%c", & cmp);
  if (cmp == '1') {
    iShowBMP2(455, 484 - 420, "tick_box.bmp", 0xffffff);
  }
  fclose(fp);
  cmp = '0';

  fp = fopen("tick16_week.txt", "r");
  fscanf(fp, "%c", & cmp);
  if (cmp == '1') {
    iShowBMP2(455, 484 - 450, "tick_box.bmp", 0xffffff);
  }
  fclose(fp);
  cmp = '0';

  fp = fopen("tick17_week.txt", "r");
  fscanf(fp, "%c", & cmp);
  if (cmp == '1') {
    iShowBMP2(455, 484 - 480, "tick_box.bmp", 0xffffff);
  }
  fclose(fp);
  cmp = '0';
  iSetColor(0, 0, 0);
  char task_str[20];
  sprintf(task_str, "%d", task);
  iText(10, 560, task_str, GLUT_BITMAP_TIMES_ROMAN_10);
  show_file();
  show_time();
  read_deadline_file();
  show_remaining_time();
  iText(882, 183, "WEEKLY TO-DO LIST", GLUT_BITMAP_TIMES_ROMAN_24);
  iText(175, 70, "CLEAR TASKS", GLUT_BITMAP_HELVETICA_18);
  iText(163, 70 + 53, "DAILY TO-DO", GLUT_BITMAP_HELVETICA_18);
  iText(153, 70 + 53 + 53, "MONTHLY TO-DO", GLUT_BITMAP_HELVETICA_18);
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
    iText(890, 561, "Add deadline day ", GLUT_BITMAP_TIMES_ROMAN_24);
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
        fp = fopen("tick15_week.txt", "w");
        fprintf(fp, "1");
        fclose(fp);
      } else if (my >= 508 - 10 && my <= 508 + 10) {
        FILE * fp;
        fp = fopen("tick1_week.txt", "w");
        fprintf(fp, "1");
        fclose(fp);
      } else if (my >= 477 - 10 && my <= 477 + 10) {
        FILE * fp;
        fp = fopen("tick2_week.txt", "w");
        fprintf(fp, "1");
        fclose(fp);
      } else if (my >= 440 - 10 && my <= 440 + 10) {
        FILE * fp;
        fp = fopen("tick3_week.txt", "w");
        fprintf(fp, "1");
        fclose(fp);
      } else if (my >= 410 - 10 && my <= 410 + 10) {
        FILE * fp;
        fp = fopen("tick4_week.txt", "w");
        fprintf(fp, "1");
        fclose(fp);
      } else if (my >= 380 - 10 && my <= 380 + 10) {
        FILE * fp;
        fp = fopen("tick5_week.txt", "w");
        fprintf(fp, "1");
        fclose(fp);
      } else if (my >= 350 - 10 && my <= 350 + 10) {
        FILE * fp;
        fp = fopen("tick6_week.txt", "w");
        fprintf(fp, "1");
        fclose(fp);
      } else if (my >= 320 - 10 && my <= 320 + 10) {
        FILE * fp;
        fp = fopen("tick7_week.txt", "w");
        fprintf(fp, "1");
        fclose(fp);
      } else if (my >= 290 - 10 && my <= 290 + 10) {
        FILE * fp;
        fp = fopen("tick8_week.txt", "w");
        fprintf(fp, "1");
        fclose(fp);
      } else if (my >= 260 - 10 && my <= 260 + 10) {
        FILE * fp;
        fp = fopen("tick9_week.txt", "w");
        fprintf(fp, "1");
        fclose(fp);
      } else if (my >= 230 - 10 && my <= 230 + 10) {
        FILE * fp;
        fp = fopen("tick10_week.txt", "w");
        fprintf(fp, "1");
        fclose(fp);
      } else if (my >= 200 - 10 && my <= 200 + 10) {
        FILE * fp;
        fp = fopen("tick11_week.txt", "w");
        fprintf(fp, "1");
        fclose(fp);
      } else if (my >= 170 - 10 && my <= 170 + 10) {
        FILE * fp;
        fp = fopen("tick12_week.txt", "w");
        fprintf(fp, "1");
        fclose(fp);
      } else if (my >= 140 - 10 && my <= 140 + 10) {
        FILE * fp;
        fp = fopen("tick13_week.txt", "w");
        fprintf(fp, "1");
        fclose(fp);
      } else if (my >= 110 - 10 && my <= 110 + 10) {
        FILE * fp;
        fp = fopen("tick14_week.txt", "w");
        fprintf(fp, "1");
        fclose(fp);
      } else if (my >= 50 - 10 && my <= 50 + 10) {
        FILE * fp;
        fp = fopen("tick16_week.txt", "w");
        fprintf(fp, "1");
        fclose(fp);
      } else if (my >= 20 - 10 && my <= 20 + 10) {
        FILE * fp;
        fp = fopen("tick17_week.txt", "w");
        fprintf(fp, "1");
        fclose(fp);
      }
    } else if (mx >= 130 && mx <= 347 && my >= 57 && my <= 101) {
      remove("deadline_week.txt");
      remove("to-do list_week.txt");
      task = 1;
      remove("task.txt");
      remove("deadline_string.txt");
      remove("tick1_week.txt");
      remove("tick2_week.txt");
      remove("tick3_week.txt");
      remove("tick4_week.txt");
      remove("tick5_week.txt");
      remove("tick6_week.txt");
      remove("tick7_week.txt");
      remove("tick8_week.txt");
      remove("tick9_week.txt");
      remove("tick10_week.txt");
      remove("tick11_week.txt");
      remove("tick12_week.txt");
      remove("tick13_week.txt");
      remove("tick14_week.txt");
      remove("tick15_week.txt");
      remove("tick16_week.txt");
      remove("tick17_week.txt");

    }
  }
}

void iKeyboard(unsigned char key) {

}

void iSpecialKeyboard(unsigned char key) {
  // Nothing here yet
}
