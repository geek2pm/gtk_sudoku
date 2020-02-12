#include <gtk/gtk.h>
#include <stdlib.h>
#include <time.h>
GtkWidget *window;
GtkWidget *used_time;
GtkWidget *fixed;
GtkWidget *grid;

#define BLOCK_SIZE 90
#define FONT_SIZE 30



int used_time_h,used_time_m,used_time_s;
used_time_h=0;
used_time_m=0;
used_time_s=0;

gboolean timer_handler();
GtkWidget *entrys[81];
int *maps[3];
int *map;

int map1[81]={4,1,2,5,6,0,8,7,9,
             0,8,6,4,7,2,5,0,0,
             0,5,3,0,0,1,0,2,4,
             0,7,5,2,4,9,3,8,6,
             0,2,9,6,0,5,1,4,0,
             3,6,4,7,1,8,2,9,0,
             5,3,0,9,0,0,7,6,0,
             0,0,8,1,2,7,4,5,0,
             2,4,7,0,5,6,9,1,8};

int map2[81]={9,2,7,6,8,4,0,3,5,
              4,8,6,3,5,1,9,7,2,
              1,5,3,7,2,9,4,6,8,
              0,1,5,2,9,7,6,8,0,
              0,4,8,5,1,3,0,2,9,
              2,7,9,4,0,8,0,1,3,
              8,6,4,1,0,5,2,9,7,
              7,9,0,8,0,6,3,0,1,
              5,3,1,9,7,2,8,4,6};

int map3[81]={9,0,2,5,4,7,3,6,0,
              4,6,5,0,0,3,0,2,7,
              7,3,0,9,2,6,8,0,5,
              0,0,6,8,1,5,4,7,9,
              8,0,9,3,6,4,5,0,2,
              5,1,4,0,7,0,0,8,3,
              1,5,7,0,9,8,2,0,6,
              2,4,0,6,0,1,0,9,0,
              0,9,8,7,3,0,1,5,4};

PangoAttrList *attrls;
PangoAttribute *attr;
PangoFontDescription *df;

void destroy(GtkWidget *widget,gpointer data)
{
    gtk_main_quit();
}
void check(GtkWidget *widget,gpointer data)
{   
    int numbers[81];
    char *s = gtk_entry_get_text (entrys[5]);
    printf("check\n");
    printf("%s\n",s);
    int map_index=0;
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            int num = map[map_index];      
            if (num==0)
            {
                char *number = gtk_entry_get_text (GTK_ENTRY(entrys[map_index]));
                int n = atoi(number);
                printf("%d",n);
                numbers[map_index]=n;
            }
            else
            {
                printf("%d",num);
                numbers[map_index]=num;
            }
            
            map_index++;
        }
        printf("\n");
    }

    int ok = 1;
    map_index=0;
    for(int i = 0; i < 9; i++)
    {
        int x=0;
        for(int j = 0; j < 9; j++)
        {
            int num = numbers[map_index];
            x+=num;
            map_index++;
        }
        if (x!=45)
        {
            printf("[%d]err\n",i);
            ok = 0;
        }else
        {
            printf("[%d]ok\n",i);
        }
    }

    
    for(int i = 0; i < 9; i++)
    {
        int x=0;
        map_index=i;
        
        for(int j = 0; j < 9; j++)
        {
            int num = numbers[map_index];
            x+=num;
            map_index+=9;
            printf("%d\n",num);
        }
        if (x!=45)
        {
            printf("[%d]err\n",i);
            ok = 0;
        }else
        {
            printf("[%d]ok\n",i);
        }
    }
    if(ok)
    {
        printf("you win!");
        GtkWidget *dialog;
        dialog = gtk_message_dialog_new(NULL,
                GTK_DIALOG_DESTROY_WITH_PARENT,
                GTK_MESSAGE_INFO,
                GTK_BUTTONS_OK,
                "\nyou win!\n");
        gtk_window_set_title(GTK_WINDOW(dialog), "success");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }else
    {
        printf("you lose!");
        GtkWidget *dialog;
        dialog = gtk_message_dialog_new(NULL,
                GTK_DIALOG_DESTROY_WITH_PARENT,
                GTK_MESSAGE_INFO,
                GTK_BUTTONS_OK,
                "\nyou lose!\n");
        gtk_window_set_title(GTK_WINDOW(dialog), "fail");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

void change(GtkEntry *entry,gchar *preedit,gpointer data)
{
//    printf("event\n");
//    char *num = gtk_entry_get_text (GTK_ENTRY(entry));
//    printf("%s\n",num);
}
int arandom(int max){
    return rand()%max;
}
void game_random()
{
    gtk_container_remove (GTK_CONTAINER (fixed), grid);
    grid = gtk_grid_new ();
    gtk_grid_set_column_spacing (grid,4);
    gtk_grid_set_row_spacing (grid,4);
    gtk_fixed_put (fixed,grid,10,10);
    gtk_widget_show (grid);
    srand(time(NULL));
    int index = arandom(3);
    printf("%d\n",index);
    
    used_time_h=0;
    used_time_m=0;
    used_time_s=0;
    map=maps[index];

    int map_index=0;

    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            int num = map[map_index];
            attrls = pango_attr_list_new ();
            df = pango_font_description_new();
            pango_font_description_set_family(df, "Ani");
            pango_font_description_set_size(df, FONT_SIZE * PANGO_SCALE);
            pango_font_description_set_weight(df, PANGO_WEIGHT_BOLD);
            attr = pango_attr_font_desc_new(df);
            pango_attr_list_insert(attrls, attr);
            pango_font_description_free(df);

            
            if (num==0)
            {
                GtkWidget *entry;
                entrys[map_index] = gtk_entry_new ();
                gtk_entry_set_alignment (GTK_ENTRY (entrys[map_index]),0.5);
                
                gtk_entry_set_width_chars (entrys[map_index],1);
                gtk_entry_set_max_length(entrys[map_index],1);
                
                
                
                g_signal_connect(entrys[map_index], "changed",change,NULL);

                GdkColor color;
                color.red = 49344;
                color.green = 49344;
                color.blue = 49344;
                gtk_widget_modify_bg(GTK_ENTRY(entrys[map_index]), GTK_STATE_NORMAL, &color);
                //font color
                attr = pango_attr_foreground_new(0,0,65535);
                pango_attr_list_change(attrls, attr);
                gtk_entry_set_attributes(GTK_ENTRY(entrys[map_index]), attrls);
                gtk_widget_set_size_request(entrys[map_index],BLOCK_SIZE,BLOCK_SIZE);
                gtk_grid_attach (grid, entrys[map_index],j,i,1,1);
                gtk_widget_show (entrys[map_index]);
            }
            else
            {
                char title[2];
                sprintf(title, "%d", num);
                GtkWidget *label;
                label = gtk_label_new_with_mnemonic (title);
                GdkColor color;
                color.red = 65535;
                color.green = 65535;
                color.blue = 65535;
                gtk_widget_modify_bg(label,GTK_STATE_NORMAL, &color);
                
                //font color
                attr = pango_attr_foreground_new(0,0,0);
                pango_attr_list_change(attrls, attr);
                gtk_label_set_attributes(GTK_LABEL(label), attrls);
                
                gtk_grid_attach (grid, label,j,i,1,1);
                gtk_widget_set_size_request(label,BLOCK_SIZE,BLOCK_SIZE);
                gtk_widget_show (label);
            }
            map_index++;
            pango_attr_list_unref(attrls);
        }  
    }

}



gboolean showtime()
{
    used_time_s++;
    if (used_time_s>59)
    {
        used_time_m++;
        used_time_s=0;
    }
    if (used_time_m>59)
    {
        used_time_h++;
        used_time_m=0;
    }

    char *s_h[2];
    char *s_m[2];
    char *s_s[2];
    
    if(used_time_s<10)
    {
        sprintf(s_s, "0%d",used_time_s);
    }else
    {
        sprintf(s_s, "%d",used_time_s);
    }
    
    

    if(used_time_m<10)
    {
        sprintf(s_m, "0%d",used_time_m);
    }else
    {
        sprintf(s_m, "%d",used_time_m);
    }
//    printf("%d:%d:%d\n",used_time_h,used_time_m,used_time_s);

//
    if(used_time_h<10)
    {
        sprintf(s_h, "0%d",used_time_h);
    }else
    {
        sprintf(s_h, "%d",used_time_h);
    }
    char *use_time[8];
    sprintf(use_time, "%s:%s:%s", s_h,s_m,s_s);
    gtk_label_set_text(GTK_LABEL(used_time),use_time);
    return TRUE;
}
int main(int argc,char *argv[])
{
    maps[0]=map1;
    maps[1]=map2;
    maps[2]=map3;
    
    gtk_init (&argc, &argv);
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window),1100,862);
    
    g_signal_connect(window, "destroy",G_CALLBACK (destroy), NULL);

//    GError **err;
//    gtk_window_set_icon_from_file (GTK_WINDOW(window),"icon.png",err);

    gtk_window_set_title(GTK_WINDOW(window),"sodoku");
    gtk_window_set_keep_above(GTK_WINDOW (window), TRUE);
    gtk_window_set_resizable (GTK_WINDOW(window),FALSE);

    GdkColor color;
    color.red = 0x00C0;
    color.green = 0x00DE;
    color.blue = 0x00ED;
    gtk_widget_modify_bg(GTK_WINDOW (window), GTK_STATE_NORMAL, &color);


    fixed = gtk_fixed_new ();
    grid = gtk_grid_new();


    gtk_container_add (GTK_CONTAINER (window), fixed);
    gtk_grid_set_column_spacing (grid,4);
    gtk_grid_set_row_spacing (grid,4);
    gtk_fixed_put (fixed,grid,10,10);

    GtkWidget *btn = gtk_button_new_with_mnemonic ("check");
    gtk_widget_set_size_request(btn,150,50);
    g_signal_connect(btn, "clicked",G_CALLBACK(check), NULL);
    gtk_fixed_put (GTK_FIXED(fixed),btn,900,300);

    GtkWidget *btn_random = gtk_button_new_with_mnemonic ("random");
    gtk_widget_set_size_request(btn_random,150,50);
    g_signal_connect(btn_random, "clicked",G_CALLBACK(game_random), NULL);
    gtk_fixed_put (GTK_FIXED(fixed),btn_random,900,400);
    
    used_time = gtk_label_new_with_mnemonic ("");
    gtk_widget_set_size_request(used_time,150,50);
    
    attrls = pango_attr_list_new ();
    df = pango_font_description_new();
    pango_font_description_set_family(df, "Ani");
    pango_font_description_set_size(df, 20 * PANGO_SCALE);
    pango_font_description_set_weight(df, PANGO_WEIGHT_BOLD);

    attr = pango_attr_font_desc_new(df);
    pango_attr_list_insert(attrls, attr);
    pango_font_description_free(df);

    attr = pango_attr_foreground_new(65535,0,0);
    pango_attr_list_change(attrls, attr);
    gtk_label_set_attributes(GTK_LABEL(used_time), attrls);

    gtk_fixed_put (GTK_FIXED(fixed),used_time,900,200);
//    gtk_container_add (GTK_CONTAINER (fixed), grid);
    game_random();
   
    gtk_widget_show_all (window);
    g_timeout_add_seconds (1, (GSourceFunc) showtime,NULL);

    gtk_main ();
    return 0;
}

