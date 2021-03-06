/*
 * support.c - Some support functions. Some are borrowed from Glade.
 *
 * Copyright (C) 2000 Archit Baweja
 * 
 * Author(s):
 *	Archit Baweja <bighead@crosswinds.net>
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


#include <gnome.h>

#include "support.h"

/*
 * This is a dummy pixmap we use when a pixmap can't be found.
 */
static char *dummy_pixmap_xpm[] = {
/* columns rows colors chars-per-pixel */
"1 1 1 1",
"  c None",
/* pixels */
" ",
" "
};

/*
 * This is an internally used function to create pixmaps.
 */
static GtkWidget *create_dummy_pixmap (GtkWidget *widget)
{
	GdkColormap *colormap;
	GdkPixmap *gdkpixmap;
	GdkBitmap *mask;
	GtkWidget *pixmap;

	colormap = gtk_widget_get_colormap (widget);
	gdkpixmap = gdk_pixmap_colormap_create_from_xpm_d (NULL, colormap, &mask,
							NULL, dummy_pixmap_xpm);
	if (gdkpixmap == NULL)
		g_error ("Couldn't create replacement pixmap.");

	pixmap = gtk_pixmap_new (gdkpixmap, mask);
	gdk_pixmap_unref (gdkpixmap);
	gdk_bitmap_unref (mask);

	return pixmap;
}

/*
 * This is an internally used function to create pixmaps.
 */
GtkWidget *create_pixmap (GtkWidget *widget,
                          const gchar *filename)
{
	GtkWidget *pixmap;
	GdkColormap *colormap;
	GdkPixmap *gdkpixmap;
	GdkBitmap *mask;
	gchar *pathname;

	pathname = g_strdup_printf ("%s/%s", ICONDIR, filename);

	if (!pathname) {
		g_warning (_("Couldn't find pixmap file: %s"), filename);
		return create_dummy_pixmap (widget);
	}

	colormap = gtk_widget_get_colormap (widget);
	gdkpixmap = gdk_pixmap_colormap_create_from_xpm (NULL, colormap, &mask,
	                                                 NULL, pathname);
	if (gdkpixmap == NULL) {
		g_warning (_("Couldn't create pixmap from file: %s"), pathname);
		g_free (pathname);
		return create_dummy_pixmap (widget);
	}
	g_free (pathname);

	pixmap = gtk_pixmap_new (gdkpixmap, mask);
	gdk_pixmap_unref (gdkpixmap);
	gdk_bitmap_unref (mask);

	return pixmap;
}

/*
 * Sets a tooltip, specified in 'tooltip_str' for the 'widget'.
 */
void set_tooltip (GtkWidget *widget, const gchar *tooltip_str)
{
	GtkTooltips *tmp_tooltip;

	tmp_tooltip = gtk_tooltips_new ();
	gtk_tooltips_set_tip (tmp_tooltip, widget, tooltip_str, NULL);

	return;
}
