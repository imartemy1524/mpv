/*
 * This file is part of mplayer.
 *
 * mplayer is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * mplayer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with mplayer.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MPLAYER_PLAYLIST_H
#define MPLAYER_PLAYLIST_H

#include <stdbool.h>
#include "core/bstr.h"

struct playlist_param {
    bstr name, value;
};

struct playlist_entry {
    struct playlist_entry *prev, *next;
    struct playlist *pl;

    char *filename;

    struct playlist_param *params;
    int num_params;
};

struct playlist {
    struct playlist_entry *first, *last;

    // This provides some sort of stable iterator. If this entry is removed from
    // the playlist, current is set to the next element (or NULL), and
    // current_was_replaced is set to true.
    struct playlist_entry *current;
    bool current_was_replaced;
};

void playlist_entry_add_param(struct playlist_entry *e, bstr name, bstr value);
void playlist_entry_add_params(struct playlist_entry *e,
                               struct playlist_param *params,
                               int params_count);

struct playlist_entry *playlist_entry_new(const char *filename);

void playlist_insert(struct playlist *pl, struct playlist_entry *after,
                     struct playlist_entry *add);
void playlist_add(struct playlist *pl, struct playlist_entry *add);
void playlist_remove(struct playlist *pl, struct playlist_entry *entry);
void playlist_clear(struct playlist *pl);

void playlist_move(struct playlist *pl, struct playlist_entry *entry,
                   struct playlist_entry *at);

void playlist_add_file(struct playlist *pl, const char *filename);
void playlist_shuffle(struct playlist *pl);
struct playlist_entry *playlist_get_next(struct playlist *pl, int direction);
void playlist_add_base_path(struct playlist *pl, bstr base_path);
void playlist_transfer_entries(struct playlist *pl, struct playlist *source_pl);

int playlist_entry_to_index(struct playlist *pl, struct playlist_entry *e);
int playlist_entry_count(struct playlist *pl);
struct playlist_entry *playlist_entry_from_index(struct playlist *pl, int index);

#endif
