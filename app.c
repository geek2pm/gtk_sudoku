#include <gtk/gtk.h>
#include <stdlib.h>
#include <time.h>
GtkWidget *window;
GtkWidget *used_time;
GtkWidget *fixed;
GtkWidget *grid;

#define BLOCK_SIZE 80

int used_time_h,used_time_m,used_time_s;
used_time_h=0;
used_time_m=0;
used_time_s=0;

gboolean timer_handler();
GtkWidget *entrys[81];
int *maps[3];
int *map;
int level=0;

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

void css(GtkWidget *widget, const gchar *data)
{
    GtkCssProvider *provider = gtk_css_provider_new ();
    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    gtk_css_provider_load_from_data(provider, data, -1, NULL);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    g_object_unref (provider);
}
void destroy(GtkWidget *widget,gpointer data)
{
    gtk_main_quit();
}
void check(GtkWidget *widget,gpointer data)
{   
    int numbers[81];
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
    GtkWidget *dialog;
    if(ok)
    {
        printf("you win!");
        dialog = gtk_message_dialog_new(NULL,
                GTK_DIALOG_DESTROY_WITH_PARENT,
                GTK_MESSAGE_INFO,
                GTK_BUTTONS_OK,
                "\nyou win!\n");
        gtk_window_set_title(GTK_WINDOW(dialog), "success");
        
    }else
    {
        printf("you lose!");
        
        dialog = gtk_message_dialog_new(NULL,
                GTK_DIALOG_DESTROY_WITH_PARENT,
                GTK_MESSAGE_INFO,
                GTK_BUTTONS_OK,
                "\nyou lose!\n");
        gtk_window_set_title(GTK_WINDOW(dialog), "fail");
        
    }
    // set center
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ON_PARENT);
    gtk_window_set_transient_for(dialog,window);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
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
void game_new()
{
    gtk_container_remove (GTK_CONTAINER (fixed), grid);
    grid = gtk_grid_new ();
//    gtk_grid_set_column_spacing (grid,4);
//    gtk_grid_set_row_spacing (grid,4);
    gtk_fixed_put (fixed,grid,0,0);
    gtk_widget_show (grid);
    srand(time(NULL));
//    int index = arandom(3);
    printf("%d\n",index);
    
    used_time_h=0;
    used_time_m=0;
    used_time_s=0;
    map=maps[level];

    int map_index=0;

    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            int num = map[map_index];
            if (num==0)
            {
                entrys[map_index] = gtk_entry_new ();
                gtk_widget_set_size_request(entrys[map_index],BLOCK_SIZE,BLOCK_SIZE);
                gtk_entry_set_alignment (GTK_ENTRY (entrys[map_index]),0.5);
                
                gtk_entry_set_width_chars (entrys[map_index],1);
                gtk_entry_set_max_length(entrys[map_index],1);
               
                g_signal_connect(entrys[map_index], "changed",change,NULL);
                css (entrys[map_index], "entry{border-radius:0px;border:solid 1px #000;background-color:#777;color:#ccc;font-size:30px}");
                gtk_grid_attach (grid, entrys[map_index],j,i,1,1);
                gtk_widget_show (entrys[map_index]);
            }
            else
            {
                char title[2];
                sprintf(title, "%d", num);
                GtkWidget *label;
                label = gtk_label_new_with_mnemonic (title);
                gtk_widget_set_size_request(label,BLOCK_SIZE,BLOCK_SIZE);
                css (label, "label{border-radius:0px;border:solid 1px #000;background-color:#ccc;color:#222;font-size:30px}");
                gtk_grid_attach (grid, label,j,i,1,1);
                gtk_widget_show (label);
            }
            map_index++;
        }  
    }
    level++;
    if(level>2){
        level=0;
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
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    
    g_signal_connect(window, "destroy",G_CALLBACK (destroy), NULL);

//    GError **err;
//    gtk_window_set_icon_from_file (GTK_WINDOW(window),"icon.png",err);

    gtk_window_set_title(GTK_WINDOW(window),"sodoku");
    gtk_window_set_keep_above(GTK_WINDOW (window), TRUE);
    gtk_window_set_resizable (GTK_WINDOW(window),FALSE);

    fixed = gtk_fixed_new ();
    gtk_widget_set_name ( fixed, "fixed_layput" );
    css (fixed, "#fixed_layput{border:solid 1px #000;}");

    grid = gtk_grid_new();
    
    gtk_container_add (GTK_CONTAINER (window), fixed);
    gtk_fixed_put (fixed,grid,0,0);

    GtkWidget *btn = gtk_button_new_with_mnemonic ("check");
    gtk_widget_set_size_request(btn,150,50);
    css (btn, "button{font-size:20px;}");
    g_signal_connect(btn, "clicked",G_CALLBACK(check), NULL);
    gtk_fixed_put (GTK_FIXED(fixed),btn,730,300);

    GtkWidget *btn_new = gtk_button_new_with_mnemonic ("New");
    gtk_widget_set_size_request(btn_new,150,50);
    css (btn_new, "button{font-size:20px;}");
    g_signal_connect(btn_new, "clicked",G_CALLBACK(game_new), NULL);
    gtk_fixed_put (GTK_FIXED(fixed),btn_new,730,360);
    
    used_time = gtk_label_new_with_mnemonic ("");
    gtk_widget_set_size_request(used_time,150,50);
    css (used_time, "label{font-size:30px;}");
    gtk_fixed_put (GTK_FIXED(fixed),used_time,730,200);
    game_new();
   
    gtk_widget_show_all (window);
    g_timeout_add_seconds (1, (GSourceFunc) showtime,NULL);

    gtk_main ();
    return 0;
}
