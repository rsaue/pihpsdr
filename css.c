/* Copyright (C)
* 2017 - John Melton, G0ORX/N6LYT
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <https://www.gnu.org/licenses/>.
*
*/

#include <gtk/gtk.h>
#include "css.h"
#include "message.h"

//
// Unless we want a special effect, do not specify colors so
// we inherit them from the GTK them.
//
// Here, only the color for the "selected" state
// (white text on a red button) is specified
//
//
char *css =
  "  @define-color TOGGLE_ON  rgb(100%,0%,0%);\n"
  "  @define-color POPUP      rgb(100%,33%,33%);\n"
  "  #small_button {\n"
  "    padding: 1px;\n"
  "    font-family: Sans;\n"
  "    font-size: 15px;\n"
  "    }\n"
  "  #small_toggle_button {\n"
  "    padding: 1px;\n"
  "    font-family: Sans;\n"
  "    font-size: 15px;\n"
  "    background-image: none;\n"
  "    }\n"
  "  #small_toggle_button:checked {\n"
  "    padding: 1px;\n"
  "    font-family: Sans;\n"
  "    font-size: 15px;\n"
  "    background-image: none;\n"           // if checked, white text on red background
  "    background-color: @TOGGLE_ON;\n"
  "    color: @COLOR_ON;\n"
  "    }\n"
  "  #popup_scale slider {\n"
  "     background: @POPUP;\n"
  "    }\n"
  "  #popup_scale trough {\n"
  "     background: @POPUP;\n"
  "    }\n"
  "  #popup_scale value {\n"
  "     color: @POPUP;\n"
  "    }\n"
  ;

void load_css() {
  GtkCssProvider *provider;
  GdkDisplay *display;
  GdkScreen *screen;
  t_print("%s\n", __FUNCTION__);
  provider = gtk_css_provider_new ();
  display = gdk_display_get_default ();
  screen = gdk_display_get_default_screen (display);
  gtk_style_context_add_provider_for_screen (screen,
      GTK_STYLE_PROVIDER(provider),
      GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  gtk_css_provider_load_from_data(provider, css, -1, NULL);
  g_object_unref (provider);
}
