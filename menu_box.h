void menu_box(int h, int w)
{
    printf("\t\t%c",201);
    for (int a=0;a<w;a++) printf("%c",205);
    printf("%c\n",187);
    for (int b=0;b<h;b++) {
        printf("\t\t%c",186);
        for (int c=0;c<w;c++) printf(" ");
        printf("%c\n",186);
    }
    printf("\t\t%c",200);
    for (int a=0;a<w;a++) printf("%c",205);
    printf("%c\n",188);
}
