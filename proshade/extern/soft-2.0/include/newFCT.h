/***************************************************************************
  **************************************************************************
    
  Spherical Harmonic Transform Kit 2.7
    
  Copyright 1997-2003  Sean Moore, Dennis Healy,
                       Dan Rockmore, Peter Kostelec
  Copyright 2004  Peter Kostelec, Dan Rockmore

  This file is part of SpharmonicKit.

  SpharmonicKit is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 3 of the License, or
  (at your option) any later version.

  SpharmonicKit is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
  
  See the accompanying LICENSE file for details.

  ************************************************************************
  ************************************************************************/

/* externally available commands from newFCT.c */

#ifndef _NEWFCT_H
#define _NEWFCT_H


extern void ExpIFCT( double * ,
		     double * ,
		     double * ,
		     int ,
		     int ,
		     int );

extern void kFCT(double *,
		 double *,
		 double *,
		 int ,
		 int ,
		 int );

#endif /* _NEWFCT_H */
