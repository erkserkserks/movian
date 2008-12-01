/*
 *  Input key mapper
 *  Copyright (C) 2008 Andreas �man
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KEYMAPPER_H
#define KEYMAPPER_H

#include <libhts/htsthreads.h>
#include "prop.h"
#include "event.h"

LIST_HEAD(keymap_entry_list, keymap_entry);

/**
 * A keymap entry is used to translate a keycode (ascii-string)
 * into an event
 */
typedef struct keymap_entry {
  LIST_ENTRY(keymap_entry) ke_link;
  char *ke_keycode;
  event_type_t ke_event;
} keymap_entry_t;


/**
 * We support having multiple keymaps, one global, and locals per
 * user interface instance
 */
typedef struct keymap {
  struct keymap_entry_list km_entries;
  hts_mutex_t km_mutex;
  prop_t *km_settings;   /* Pointer to settings in settings tree */
} keymap_t;



/**
 *
 */
event_t *keymapper_resolve(keymap_t *km, const char *str);

void keymapper_deliver(keymap_t *km, const char *str);

void keymapper_init(keymap_t *km, prop_t *settingsparent, const char *title);

#endif /* KEYMAPPER_H */
