/* Copyright (C)
* 2017 - John Melton, G0ORX/N6LYT
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
* Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*
*/

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <gtk/gtk.h>
#include "main.h"
#include "discovery.h"
#include "receiver.h"
#include "sliders.h"
#include "toolbar.h"
#include "vfo.h"
#include "radio.h"
#include "radio_menu.h"
#include "new_menu.h"
#include "noise_menu.h"
#include "ext.h"
#include "zoompan.h"
#include "equalizer_menu.h"


// The following calls functions can be called usig g_idle_add

int ext_discovery(void *data) {
  discovery();
  return 0;
}

//
// ALL calls to vfo_update should go through g_idle_add(ext_vfo_update)
// such that they can be filtered out if they come at high rate
//
static guint vfo_timeout=0;

static int vfo_timeout_cb(void * data) {
  vfo_timeout=0;
  vfo_update();
  return 0;
}

int ext_vfo_update(void *data) {
  if (vfo_timeout==0) {
    vfo_timeout=g_timeout_add(100, vfo_timeout_cb, NULL);
  }
  return 0;
}

int ext_mox_update(void *data) {
  mox_update(GPOINTER_TO_INT(data));
  return 0;
}

int ext_vox_changed(void *data) {
  vox_changed(GPOINTER_TO_INT(data));
  return 0;
}

int ext_sliders_update(void *data) {
  sliders_update();
  return 0;
}

int ext_start_band(void *data) {
  start_band();
  return 0;
}

int ext_start_vfo(void *data) {
  int val=GPOINTER_TO_INT(data);
  start_vfo(val);
  return 0;
}

int ext_start_rx(void *data) {
  start_rx();
  return 0;
}

int ext_start_tx(void *data) {
  start_tx();
  return 0;
}

int ext_update_noise(void *data) {
  update_noise();
  return 0;
}

int ext_update_eq(void *data) {
  update_eq();
  return 0;
}

int ext_set_duplex(void *data) {
  setDuplex();
  return 0;
}

#ifdef CLIENT_SERVER
int ext_receiver_remote_update_display(void *data) {
  RECEIVER *rx=(RECEIVER *)data;
  receiver_remote_update_display(rx);
  return 0;
}
int ext_remote_set_zoom(void *data) {
  int zoom=GPOINTER_TO_INT(data);
  remote_set_zoom(active_receiver->id,(double)zoom);
  return 0;
}

int ext_remote_set_pan(void *data) {
  int pan=GPOINTER_TO_INT(data);
  remote_set_pan(active_receiver->id,(double)pan);
  return 0;
}

int ext_set_title(void *data) {
  gtk_window_set_title(GTK_WINDOW(top_window),(char *)data);
  return 0;
}
#endif
