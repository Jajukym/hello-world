#include <stdio.h>
#include <gtk/gtk.h>

GtkWidget *txt;
GtkWidget *txt2;
int pos = 0;



void end_program (GtkWidget *wid, gpointer ptr)
{
	gtk_main_quit ();
}

void copy_text (GtkWidget *wid, gpointer ptr)
{
	const char *input = gtk_entry_get_text (GTK_ENTRY (txt));
	gtk_label_set_text (GTK_LABEL (ptr), input);
}

void check_toggle (GtkWidget *wid, gpointer ptr)
{
	printf ("The state of the button is %d\n",
	gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (wid)));
}

void combo_changed (GtkWidget *wid, gpointer ptr)
{
	int sel = gtk_combo_box_get_active (GTK_COMBO_BOX (wid));
	char *selected = gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT (wid));
	printf ("The value of the combo is %d %s\n", sel, selected);
}



int main (int argc, char *argv[])
{
	gtk_init (&argc, &argv); //initialize
	
	/*Create window*/
	GtkWidget *win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	/*Add function to "x" button*/
	g_signal_connect (win, "delete_event", G_CALLBACK (end_program), NULL);
	
	/*User inputs************/
	
	GtkWidget *lbl = gtk_label_new ("My label"); /*Create label and text output*/
	
	GtkWidget *btn2 = gtk_button_new_with_label ("Copy"); /*Create a copy button and add function*/
	g_signal_connect (btn2, "clicked", G_CALLBACK (copy_text), lbl);
	
	txt = gtk_entry_new (); /*data entry*/
	
	GtkObject *adj = gtk_adjustment_new (0, -10, 10, 1, 0, 0); /*Create numeric spin box*/
	txt2 = gtk_spin_button_new (GTK_ADJUSTMENT (adj), 0, 0);
	
	GtkWidget *chk = gtk_check_button_new_with_label ("My check"); /*Create check box*/
	g_signal_connect (chk, "toggled", G_CALLBACK (check_toggle),NULL);
	int state = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (chk)); /*Instant check of state*/
	printf("Check State %d\n", state);
			
	GtkWidget *rad1 = gtk_radio_button_new_with_label (NULL,"TRUE"); /*List of radio buttons*/
	GSList *group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (rad1));
	GtkWidget *rad2 = gtk_radio_button_new_with_label (group,"FALSE");
	int sel1 = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (rad1)); /*Instant check of state*/
	printf("Select State %d\n", sel1);
	int sel2 = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (rad2)); /*Instant check of state*/
	printf("Select State %d\n", sel2);
	
	GtkWidget *comb = gtk_combo_box_text_new (); /*Create drop down*/
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (comb),"Option 1");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (comb),"Option 2");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (comb),"Option 3");
	gtk_combo_box_set_active (GTK_COMBO_BOX (comb), 0);
	g_signal_connect (comb, "changed", G_CALLBACK (combo_changed),NULL);
	int sel = gtk_combo_box_get_active (GTK_COMBO_BOX (comb)); /*Instant check of option*/
	printf("Option %d is active. \n", sel);
	char *selected = gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT (comb));
	
	int pos = 0;
	GtkListStore *ls = gtk_list_store_new (1, G_TYPE_STRING);
	gtk_list_store_insert_with_values (ls, NULL, pos++, 0,"Option 1", -1);
	gtk_list_store_insert_with_values (ls, NULL, pos++, 0,"Option 2", -1);
	gtk_list_store_insert_with_values (ls, NULL, pos++, 0,"Option 3", -1);
	GtkWidget *comb2 = gtk_combo_box_new_with_model (GTK_TREE_MODEL (ls));
	GtkCellRenderer *rend = gtk_cell_renderer_text_new ();
	gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (comb2), rend, FALSE);
	gtk_cell_layout_add_attribute (GTK_CELL_LAYOUT (comb2), rend,"text", 0);
	
	
	/*Create close button and add function*/
	GtkWidget *btn = gtk_button_new_with_label ("Close window");
	g_signal_connect (btn, "clicked", G_CALLBACK (end_program), NULL);
	
	/*Create container and order widgets*/
	GtkWidget *tab = gtk_table_new (4, 4, TRUE);
	gtk_table_attach_defaults (GTK_TABLE (tab), lbl, 0, 1, 0, 1);
	gtk_table_attach_defaults (GTK_TABLE (tab), btn2, 1, 2, 1, 2);
	gtk_table_attach_defaults (GTK_TABLE (tab), btn, 0, 1, 3, 4);
	gtk_table_attach_defaults (GTK_TABLE (tab), txt, 1, 2, 0, 1);
	gtk_table_attach_defaults (GTK_TABLE (tab), txt2, 1, 2, 2, 3);
	gtk_table_attach_defaults (GTK_TABLE (tab), chk, 1, 2, 3, 4);
	gtk_table_attach_defaults (GTK_TABLE (tab), rad1, 0, 1, 1, 2);
	gtk_table_attach_defaults (GTK_TABLE (tab), rad2, 0, 1, 2, 3);
	gtk_table_attach_defaults (GTK_TABLE (tab), comb, 2, 3, 2, 3);
	gtk_table_attach_defaults (GTK_TABLE (tab), comb2, 3, 4, 2, 3);
	
	gtk_container_add (GTK_CONTAINER (win), tab);
	
	/*Draw window and widgets to screen*/
	gtk_widget_show_all (win);
	
	/*GTK loop function*/
	gtk_main ();
	
	return 0;
}
