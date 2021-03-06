/*
 * The Peacock HTML Editor for Gnome.
 *
 * main.c - Main entry point for program.
 * 
 * Copyright (C) 2003 Archit Baweja
 *
 * Author(s):
 *	Archit Baweja <bighead@users.sourceforge.net>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,
 * USA.
 */

#include <libbonoboui.h>
#include <libgnomeui/libgnomeui.h>

#include "peacock-window.h"

int
main (int argc, char **argv)
{
	GnomeProgram *program;
	GtkWidget *window;
	GError *error;

	bindtextdomain (PACKAGE, GNOMELOCALEDIR);
	bind_textdomain_codeset (PACKAGE, "UTF-8");
	textdomain (PACKAGE);

	program = gnome_program_init ("peacock-2", VERSION,
				      LIBGNOMEUI_MODULE, argc, argv,
				      GNOME_PARAM_HUMAN_READABLE_NAME, _("Peacock - A HTML Editor for Gnome"),
				      GNOME_PARAM_APP_DATADIR, DATADIR, NULL);


	if (bonobo_ui_init ("peacock-2", VERSION, &argc, argv) == FALSE)
		g_error ("Could not initialize Bonobo!");

	/*
	 * Create Main App Window.
	 */
	window = peacock_window_new ();
	gtk_widget_show (window);

	bonobo_main ();

	return 0;
}
