#include <gtk/gtk.h>
#include <stdlib.h>

GtkWidget *window;
gboolean timer_handler();
GtkWidget *ens[81];
GtkWidget *entrys[81];
int map[81]={4,1,2,5,6,0,8,7,9,
         0,8,6,4,7,2,5,0,0,
         0,5,3,0,0,1,0,2,4,
         0,7,5,2,4,9,3,8,6,
         0,2,9,6,0,5,1,4,0,
         3,6,4,7,1,8,2,9,0,
         5,3,0,9,0,0,7,6,0,
         0,0,8,1,2,7,4,5,0,
         2,4,7,0,5,6,9,1,8};




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
        printf("your win!");
        GtkWidget *dialog;
        dialog = gtk_message_dialog_new(NULL,
                GTK_DIALOG_DESTROY_WITH_PARENT,
                GTK_MESSAGE_INFO,
                GTK_BUTTONS_OK,
                "\n你赢了\n");
        gtk_window_set_title(GTK_WINDOW(dialog), "success");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

void change(GtkEntry *entry,gchar *preedit,gpointer data)
{
    printf("event\n");
    char *num = gtk_entry_get_text (GTK_ENTRY(entry));
//    gtk_widget_hide(GTK_LABEL(data));

//    printf("%s:%d\n",num,(int)data);
//    *a = 2;
//    
//    int * pn = user_data;
    printf("%s\n",num);
}


gboolean showtime()
{
//    GDateTime *date_time;
//    gchar *dt_format;
//    date_time = g_date_time_new_now_local();
//    dt_format = g_date_time_format(date_time, "%H:%M:%S");   
//    gtk_label_set_text(GTK_LABEL(label),dt_format);
//    g_free (dt_format);
    return TRUE;
}
int main(int argc,char *argv[])
{
    
    gtk_init (&argc, &argv);
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window),770,595);
    
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

    GtkWidget *fixed = gtk_fixed_new ();
    gtk_container_add (GTK_CONTAINER (window), fixed);

    GtkWidget *gird = gtk_grid_new();
    gtk_grid_set_column_spacing (gird,4);
    gtk_grid_set_row_spacing (gird,4);
    gtk_fixed_put (fixed,gird,10,10);

    GtkWidget *btn = gtk_button_new_with_mnemonic ("check");
    gtk_widget_set_size_request(btn,150,50);
    g_signal_connect(btn, "clicked",G_CALLBACK(check), NULL);
    
    gtk_fixed_put (GTK_FIXED(fixed),btn,600,300);
//    gtk_container_add (GTK_CONTAINER (fixed), gird);

    PangoAttrList *attrls;
    PangoAttribute *attr;
    PangoFontDescription *df;

    int map_index=0;

    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            int num = map[map_index];
            attrls = pango_attr_list_new ();
            df = pango_font_description_new();
            pango_font_description_set_family(df, "Ani");
            pango_font_description_set_size(df, 20 * PANGO_SCALE);
            pango_font_description_set_weight(df, PANGO_WEIGHT_BOLD);
            attr = pango_attr_font_desc_new(df);
            pango_attr_list_insert(attrls, attr);
            pango_font_description_free(df);

            
            if (num==0)
            {
                GtkWidget *entry;
                entrys[map_index] = gtk_entry_new ();
                gtk_entry_set_alignment (GTK_ENTRY (entrys[map_index]),0.5);
                gtk_widget_set_size_request(entrys[map_index],60,60);
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
                gtk_grid_attach (gird, entrys[map_index],j,i,1,1);
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
                gtk_widget_set_size_request(label,60,60);

                
                //font color
                attr = pango_attr_foreground_new(0,0,0);
                pango_attr_list_change(attrls, attr);
                gtk_label_set_attributes(GTK_LABEL(label), attrls);
                
                gtk_grid_attach (gird, label,j,i,1,1);
            }
            map_index++;
            pango_attr_list_unref(attrls);
        }  
    }


//
//    gtk_container_add (GTK_CONTAINER (window), label);
//    
    gtk_widget_show_all (window);
//    g_timeout_add_seconds (1, (GSourceFunc) showtime,NULL);

    gtk_main ();
    return 0;
}


