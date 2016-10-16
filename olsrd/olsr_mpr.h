/*
 * OLSR Rout(e)ing protocol
 *
 * Copyright (C) 2005        Tudor Golubenco
 *                           Polytechnics University of Bucharest 
 *
 * This program is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU General Public Licenseas published by the Free 
 * Software Foundation; either version 2 of the License, or (at your option) 
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for 
 * more details.

 * You should have received a copy of the GNU General Public License along 
 * with this program; if not, write to the Free Software Foundation, Inc., 
 * 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifndef _ZEBRA_OLSR_MPR_H
#define _ZEBRA_OLSR_MPR_H


struct olsr_1N
{
  struct olsr_neigh *on;
  struct list *hop2lst;
  int D;

  u_char marked;
  struct listnode *node;
};

struct olsr_2N
{
  struct in_addr addr;
  struct list *hop1lst;
  int lock;

  struct listnode *node;
};


/* Prototypes. */
void
olsr_is_mprs_set (struct olsr_neigh *on, float vtime);

void
olsr_mpr_update_if (struct olsr_interface *oi);

void
olsr_mpr_update (struct olsr *olsr);


#endif /* _ZEBRA_OLSR_MPR_H */
