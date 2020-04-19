/*********************************************************************
 * (C) Copyright 2000 Albert Ludwigs University Freiburg
 *     Institute of Computer Science
 *
 * All rights reserved. Use of this software is permitted for 
 * non-commercial research purposes, and it may be copied only 
 * for that use.  All copies must include this copyright message.
 * This software is made available AS IS, and neither the authors
 * nor the  Albert Ludwigs University Freiburg make any warranty
 * about the software or its performance. 
 *********************************************************************/


/**
   The following parts of this file have been modified by the 
   LPG developers (DEA - University of Brescia):
  
   Modified functions:
   - print_PlNode
**/



/*********************************************************************
 * File: output.c
 * Description: printing info out
 *
 * Author: Joerg Hoffmann
 *
 *********************************************************************/ 





#include "ff.h"

#include "output.h"
#include "lpg.h"






/* parsing
 */







void print_FactList( FactList *list, char *sepf, char *sept )

{

  FactList *i_list;
  TokenList *i_tl;
    
  if ( list ) {
    i_tl = list->item;
    if (NULL == i_tl || NULL == i_tl->item) {
      printf("empty");
    } else {
      printf("%s", i_tl->item);
      i_tl = i_tl->next;
    }
    
    while (NULL != i_tl) {
      if (NULL != i_tl->item) {
	printf("%s%s", sept, i_tl->item);
      }
      i_tl = i_tl->next;
    }
    
    for ( i_list = list->next; i_list; i_list = i_list->next ) {
      printf("%s", sepf);
      i_tl = i_list->item;
      if (NULL == i_tl || NULL == i_tl->item) {
	printf("empty");
      } else {
	printf("%s", i_tl->item);
	i_tl = i_tl->next;
      }
      
      while (NULL != i_tl) {
	if (NULL != i_tl->item) {
	  printf("%s%s", sept, i_tl->item);
	}
	i_tl = i_tl->next;
      }
    }
  }

}



void print_hidden_TokenList( TokenList *list, char *sep )

{

  TokenList *i_tl;

  i_tl = list;
  if (NULL!=i_tl) {
    printf("%s", i_tl->item);
    i_tl = i_tl->next;
  } else {
    printf("empty");
  }
  
  while (NULL != i_tl) {
    printf("%s%s", sep, i_tl->item);
    i_tl = i_tl->next;
  }
  
}



void print_indent( int indent )

{

  int i;
  for (i=0;i<indent;i++) {
    printf(" ");
  }

}



void print_PlNode( PlNode *plnode, int indent )

{

  PlNode *i_son;

  if ( !plnode ) {
    printf("none\n");
    return;
  }
  
  switch (plnode->connective) {
  case ALL: 
//    printf("ALL %s : %s\n", plnode->atom->item,
//	    plnode->atom->next->item);
//    print_indent(indent);
    printf("ALL (   ");
    print_PlNode(plnode->sons,indent+4);
    print_indent(indent);
    printf(")\n");
    break;
  case EX:
//    printf("EX  %s : %s\n", plnode->atom->item,
//	    plnode->atom->next->item);
//    print_indent(indent);
    printf("EX (   ");
    print_PlNode(plnode->sons,indent+4);
    print_indent(indent);
    printf(")\n");
    break;
  case AND: 
    printf("A(  ");
    print_PlNode(plnode->sons, indent+4);
    if ( plnode->sons ) {
      for ( i_son = plnode->sons->next; i_son!=NULL; i_son = i_son->next ) {
	print_indent(indent);
	printf("AND ");
	print_PlNode(i_son,indent+4);
      }
    }
    print_indent(indent);      
    printf(")\n");
    break;
  case OR:  
    printf("O(  ");
    print_PlNode(plnode->sons, indent+4);
    for ( i_son = plnode->sons->next; i_son!=NULL; i_son = i_son->next ) {
      print_indent(indent);
      printf("OR ");
      print_PlNode(i_son,indent+4);
    }
    print_indent(indent);      
    printf(")\n");
    break;
  case WHEN:
    printf("IF   ");
    print_PlNode(plnode->sons,indent+5);
    print_indent(indent);
    printf("THEN ");
    print_PlNode(plnode->sons->next,indent+5);
    print_indent(indent);
    printf("ENDIF\n");
    break;
  case NOT:
    if (ATOM==plnode->sons->connective) {
      printf("NOT ");
      print_PlNode(plnode->sons,indent+4);
    } else {
      printf("NOT(");
      print_PlNode(plnode->sons,indent+4);
      print_indent(indent+3);
      printf(")\n");
    }
    break;
  case ATOM:
    printf("(");
    print_hidden_TokenList(plnode->atom, " ");
    printf(")\n");
    break;
  case TRU:
     printf("(TRUE)\n");
     break;
  case FAL:
     printf("(FALSE)\n");
     break;   
/**
 * DEA - University of Brescia
 **/
    case NUM_EXP:
      printf ("NUM_EXP(");
      print_PlNode (plnode->sons, indent + 4);
      print_indent (indent + 3);
      printf (")\n");
      break;
    case BIN_COMP:
      printf ("BIN_COMP(");
      print_PlNode (plnode->sons, indent + 4);
      print_indent (indent + 3);
      printf (")\n");
      break;
    case LESS_THAN_CONN:
      printf ("< (");
      print_PlNode (plnode->sons, indent + 4);
      print_indent (indent + 3);
      print_PlNode (plnode->sons->next, indent + 4);
      print_indent (indent + 3);
      printf (")\n");
      break;
    case LESS_THAN_OR_EQUAL_CONN:
      printf ("<= (");
      print_PlNode (plnode->sons, indent + 4);
      print_indent (indent + 3);
      print_PlNode (plnode->sons->next, indent + 4);
      print_indent (indent + 3);
      printf (")\n");
      break;
    case EQUAL_CONN:
      printf ("= (");
      print_PlNode (plnode->sons, indent + 4);
      print_indent (indent + 3);
      print_PlNode (plnode->sons->next, indent + 4);
      print_indent (indent + 3);
      printf (")\n");
      break;
    case GREATER_THAN_CONN:
      printf ("> (");
      print_PlNode (plnode->sons, indent + 4);
      print_indent (indent + 3);
      print_PlNode (plnode->sons->next, indent + 4);
      print_indent (indent + 3);
      printf (")\n");
      break;
    case GREATER_OR_EQUAL_CONN:
      printf (">= (");
      print_PlNode (plnode->sons, indent + 4);
      print_indent (indent + 3);
      print_PlNode (plnode->sons->next, indent + 4);
      print_indent (indent + 3);
      printf (")\n");
      break;
    case MUL_CONN:
      printf ("(* ");
      print_PlNode (plnode->sons, indent + 4);
      print_indent (indent + 3);
      print_PlNode (plnode->sons->next, indent + 4);
      print_indent (indent + 3);
      printf (")\n");
      break;
    case DIV_CONN:
      printf ("(/ ");
      print_PlNode (plnode->sons, indent + 4);
      print_indent (indent + 3);
      print_PlNode (plnode->sons->next, indent + 4);
      print_indent (indent + 3);
      printf (")\n");
      break;
    case MINUS_CONN:
    case UMINUS_CONN:
      printf ("(- ");
      print_PlNode (plnode->sons, indent + 4);
      print_indent (indent + 3);
      print_PlNode (plnode->sons->next, indent + 4);
      print_indent (indent + 3);
      printf (")\n");
      break;
    case PLUS_CONN:
      printf ("(+ ");
      print_PlNode (plnode->sons, indent + 4);
      print_indent (indent + 3);
      print_PlNode (plnode->sons->next, indent + 4);
      print_indent (indent + 3);
      printf (")\n");
      break;
    case ASSIGN_CONN:
      printf ("ASSIGN ( ");
      print_PlNode (plnode->sons, indent + 4);
      print_indent (indent + 3);
      print_PlNode (plnode->sons->next, indent + 4);
      print_indent (indent + 3);
      printf (")\n");
      break;
    case INCREASE_CONN:
      printf ("INCREASE ( ");
      print_PlNode (plnode->sons, indent + 4);
      print_indent (indent + 3);
      print_PlNode (plnode->sons->next, indent + 4);
      print_indent (indent + 3);
      printf (")\n");
      break;
    case DECREASE_CONN:
      printf ("DECREASE ( ");
      print_PlNode (plnode->sons, indent + 4);
      print_indent (indent + 3);
      print_PlNode (plnode->sons->next, indent + 4);
      print_indent (indent + 3);
      printf (")\n");
      break;
    case SCALE_UP_CONN:
      printf ("SCALE_UP ( ");
      print_PlNode (plnode->sons, indent + 4);
      print_indent (indent + 3);
      print_PlNode (plnode->sons->next, indent + 4);
      print_indent (indent + 3);
      printf (")\n");
      break;
    case SCALE_DOWN_CONN:
      printf ("SCALE_DOWN ( ");
      print_PlNode (plnode->sons, indent + 4);
      print_indent (indent + 3);
      print_PlNode (plnode->sons->next, indent + 4);
      print_indent (indent + 3);
      printf (")\n");
      break;
    case AT_START_CONN:
      printf ("AT_START ( ");
      print_PlNode (plnode->sons, indent + 4);
      print_indent (indent + 3);
      printf (")\n");
      break;
    case AT_END_CONN:
      printf ("AT_END ( ");
      print_PlNode (plnode->sons, indent + 4);
      print_indent (indent + 3);
      printf (")\n");
      break;
    case OVER_ALL_CONN:
      printf ("OVER_ALL ( ");
      print_PlNode (plnode->sons, indent + 4);
      print_indent (indent + 3);
      printf (")\n");
      break;
    case MINIMIZE_CONN:
      printf ("MINIMIZE ( ");
      print_PlNode (plnode->sons, indent + 4);
      print_indent (indent + 3);
      printf (")\n");
      break;
    case MAXIMIZE_CONN:
      printf ("MAXIMIZE ( ");
      print_PlNode (plnode->sons, indent + 4);
      print_indent (indent + 3);
      printf (")\n");
      break;
    case METRIC_CONN:
      printf ("METRIC ( ");
      print_PlNode (plnode->sons, indent + 4);
      print_indent (indent + 3);
      printf (")\n");
      break;
    case FN_HEAD:
      printf ("FN_HEAD ( ");
      print_hidden_TokenList (plnode->atom, " ");
      printf (")\n");
      break;
    case F_EXP:
      printf ("F_EXP ( ");
      print_PlNode (plnode->sons, indent + 4);
      print_indent (indent + 3);
      printf (")\n");
      break;
    case TOTAL_TIME_CONN:
      printf ("TOTAL_TIME");
      print_PlNode (plnode->sons, indent + 4);
      print_indent (indent + 3);
      printf ("\n");
      break;
    case DURATION_VAR_ATOM:
      printf ("DURATION_VAR");
      print_indent (indent + 3);
      printf ("\n");
      break;
/**
 * End of DEA
 **/
  default:
    printf("\n***** ERROR ****");
    printf("\nprint_plnode: %d > Wrong Node specifier\n", plnode->connective);
    exit(1);
  }     

} 

void print_ConNode( ConNode *plnode, int indent )

{

  PlNode *i_son;
  ConNode *i_son_c;

  if ( !plnode ) {
    printf("none\n");
    return;
  }
  
  switch (plnode->connective) {
  case ALL_c: 
    printf("ALL ");
    print_indent(indent);
    printf("(   ");
    print_PlNode(plnode->sons,indent+4);
    print_indent(indent);
    printf(")\n");
    break;
  case ALL_c_c: 
    printf("ALL ");
    print_indent(indent);
    printf("(   ");
    print_ConNode(plnode->sons_c,indent+4);
    print_indent(indent);
    printf(")\n");
    break;
  case AND_c: 
    printf("A(  ");
    print_PlNode(plnode->sons, indent+4);
    if ( plnode->sons ) {
      for ( i_son = plnode->sons->next; i_son!=NULL; i_son = i_son->next ) {
	print_indent(indent);
	printf("AND ");
	print_PlNode(i_son,indent+4);
      }
    }
    print_indent(indent);      
    printf(")\n");
    break;
  case AND_c_c: 
    printf("A(  ");
    print_ConNode(plnode->sons_c, indent+4);
    if ( plnode->sons ) {
      for ( i_son_c = plnode->sons_c->next; i_son_c!=NULL; i_son_c = i_son_c->next ) {
	print_indent(indent);
	printf("AND ");
	print_ConNode(i_son_c,indent+4);
      }
    }
    print_indent(indent);      
    printf(")\n");
    break;
  case ATOM_c:
    printf("(");
    print_PlNode(plnode->sons, indent+4);
    printf(")\n");
    break;
  case AT_END_c:
    printf ("(AT_END ");
    print_PlNode (plnode->sons, indent + 4);
    print_indent (indent + 3);
    printf (")\n");
    break;
  case ALWAYS_c:
    printf ("(ALWAYS ");
    print_PlNode (plnode->sons, indent + 4);
    print_indent (indent + 3);
    printf (")\n");
    break;
  case SOMETIME_c:
    printf ("(SOMETIME ");
    print_PlNode (plnode->sons, indent + 4);
    print_indent (indent + 3);
    printf (")\n");
    break;
  case WITHIN_c:
    printf ("(WITHIN %f ", plnode->number);
    print_PlNode (plnode->sons, indent + 4);
    print_indent (indent + 3);
    printf (")\n");
    break;
  case AT_MOST_ONCE_c:
    printf ("(AT_MOST_ONCE ");
    print_PlNode (plnode->sons, indent + 4);
    print_indent (indent + 3);
    printf (")\n");
    break;
  case SOMETIME_AFTER_c:
    printf ("SOMETIME_AFTER (");
    print_PlNode (plnode->sons, indent + 4);
    print_indent (indent + 3);
    print_PlNode (plnode->sons2, indent + 4);
    print_indent (indent + 3);
    printf (")\n");
    break;
  case SOMETIME_BEFORE_c:
    printf ("SOMETIME_BEFORE (");
    print_PlNode (plnode->sons, indent + 4);
    print_indent (indent + 3);
    print_PlNode (plnode->sons2, indent + 4);
    print_indent (indent + 3);
    printf (")\n");
    break;
  case ALWAYS_WITHIN_c:
    printf ("ALWAYS_WITHIN %f (", plnode->number);
    print_PlNode (plnode->sons, indent + 4);
    print_indent (indent + 3);
    print_PlNode (plnode->sons2, indent + 4);
    print_indent (indent + 3);
    printf (")\n");
    break;
  case HOLD_DURING_c:
    printf ("(HOLD_DURING %f %f ", plnode->number, plnode->number2);
    print_PlNode (plnode->sons, indent + 4);
    print_indent (indent + 3);
    printf (")\n");
    break;
  case HOLD_AFTER_c:
    printf ("ALWAYS_WITHIN %f (", plnode->number);
    print_PlNode (plnode->sons, indent + 4);
    print_indent (indent + 3);
    printf (")\n");
    break;
  default:
    printf("\n***** ERROR ****");
    printf("\nprint_plnode: %d > Wrong Node specifier\n", plnode->connective);
    exit(1);
  }     

  if (plnode->next)
  {
    printf("------------------------------\n");
    print_ConNode(plnode->next, indent);
  }

} 

void print_PrefNode( PrefNode *plnode)
{
  printf("%s %s %f\n", plnode->name, plnode->opname, plnode->weight);
  print_ConNode(plnode->body, 2);  
  printf("\n");
  if (plnode->next)
  {
    printf("------------------------------\n");
    print_PrefNode(plnode->next);
  }
}

void print_plops( PlOperator *plop )

{

  PlOperator *i_plop;
  int count = 0;

  if ( !plop ) {
    printf("none\n");
  }

  for ( i_plop = plop; i_plop!=NULL; i_plop = i_plop->next ) {
    printf("\nOPERATOR ");
    printf("%s", i_plop->name);
    printf("\nparameters: (%d real)\n", i_plop->number_of_real_params);
    print_FactList ( i_plop->params, "\n", " : ");
    printf("\n\npreconditions:\n");
    print_PlNode(i_plop->preconds, 0);
    printf("effects:\n");
    print_PlNode(i_plop->effects, 0);
    printf("\n-----\n");
    count++;
  }
  printf("\nAnzahl der Operatoren: %d\n", count);

}



void print_Wff( WffNode *n, int indent )

{

  WffNode *i;

  if ( !n ) {
    printf("none\n");
    return;
  }
  
  switch (n->connective) {
  case ALL: 
    printf("ALL x%d (%s): %s\n", n->var, n->var_name,
	    gtype_names[n->var_type]);
    print_indent(indent);
    printf("(   ");
    print_Wff(n->son,indent+4);
    print_indent(indent);
    printf(")\n");
    break;
  case EX:
    printf("EX  x%d (%s) : %s\n",  n->var, n->var_name,
	    gtype_names[n->var_type]);
    print_indent(indent);
    printf("(   ");
    print_Wff(n->son,indent+4);
    print_indent(indent);
    printf(")\n");
    break;
  case AND: 
    printf("A(  ");
    print_Wff(n->sons, indent+4);
    if ( n->sons ) {
      for ( i = n->sons->next; i!=NULL; i = i->next ) {
	if ( !i->prev ) {
	  printf("\nprev in AND not correctly set!\n\n");
	  exit( 1 );
	}
	print_indent(indent);
	printf("AND ");
	print_Wff(i,indent+4);
      }
    }
    print_indent(indent);      
    printf(")\n");
    break;
  case OR:  
    printf("O(  ");
    print_Wff(n->sons, indent+4);
    for ( i = n->sons->next; i!=NULL; i = i->next ) {
      print_indent(indent);
      printf("OR ");
      print_Wff(i,indent+4);
    }
    print_indent(indent);      
    printf(")\n");
    break;
  case NOT:
    if (ATOM==n->son->connective) {
      printf("NOT ");
      print_Wff(n->son,indent+4);
    } else {
      printf("NOT(");
      print_Wff(n->son,indent+4);
      print_indent(indent+3);
      printf(")\n");
    }
    break;
  case ATOM:
    print_Fact(n->fact);
    if ( n->NOT_p != -1 ) printf(" - translation NOT");
    printf("\n");
    break;
  case TRU:
     printf("(TRUE)\n");
     break;
  case FAL:
     printf("(FALSE)\n");
     break;   
  default:
    printf("\n***** ERROR ****");
    printf("\nprint_Wff: %d > Wrong Node specifier\n", n->connective);
    exit(1);
  }     

} 



void print_Operator( Operator *o )

{

  Effect *e;
  Literal *l;
  int i, m = 0;

  printf("\n\n----------------Operator %s, translated form, step 1--------------\n", o->name);

  for ( i = 0; i < o->num_vars; i++ ) {
    printf("\nx%d (%s) of type %s, removed ? %s",
	   i, o->var_names[i], gtype_names[o->var_types[i]],
	   o->removed[i] ? "YES" : "NO");
  }
  printf("\ntotal params %d, real params %d\n", 
	 o->num_vars, o->number_of_real_params);

  printf("\nPreconds:\n");
  print_Wff( o->preconds, 0 );

  printf("\n\nEffects:");
  for ( e = o->effects; e; e = e->next ) {
    printf("\n\neffect %d, parameters %d", m++, e->num_vars);

    for ( i = 0; i < e->num_vars; i++ ) {
      printf("\nx%d (%s) of type %s",
	     o->num_vars + i, e->var_names[i], gtype_names[e->var_types[i]]);
    }
    printf("\nConditions\n");
    print_Wff( e->conditions, 0 );
    printf("\nEffect Literals");
    for ( l = e->effects; l; l = l->next ) {
      if ( l->negated ) {
	printf("\nNOT ");
      } else {
	printf("\n");
      }
      print_Fact( &(l->fact) );
    }
  }

}



void print_NormOperator( NormOperator *o )

{

  NormEffect *e;
  int i, m;

  printf("\n\n----------------Operator %s, normalized form--------------\n", 
	 o->operator->name);

  for ( i = 0; i < o->num_vars; i++ ) {
    printf("\nx%d of type ", i);
    print_type( o->var_types[i] );
  }
  printf("\n\n%d vars removed from original operator:",
	 o->num_removed_vars);
  for ( i = 0; i < o->num_removed_vars; i++ ) {
    m = o->removed_vars[i];
    printf("\nx%d (%s) of type %s, type constraint ", m, o->operator->var_names[m], 
	   gtype_names[o->operator->var_types[m]]);
    print_type( o->type_removed_vars[i] );
  }

  printf("\nPreconds:\n");
  for ( i = 0; i < o->num_preconds; i++ ) {
    print_Fact( &(o->preconds[i]) );
    printf("\n");
  }

  m = 0;
  printf("\n\nEffects:");
  for ( e = o->effects; e; e = e->next ) {
    printf("\n\neffect %d, parameters %d", m++, e->num_vars);

    for ( i = 0; i < e->num_vars; i++ ) {
      printf("\nx%d of type ", o->num_vars + i);
      print_type( e->var_types[i] );
    }
    printf("\nConditions\n");
    for ( i = 0; i < e->num_conditions; i++ ) {
      print_Fact( &(e->conditions[i]) );
      printf("\n");
    }
    printf("\nAdds\n");
    for ( i = 0; i < e->num_adds; i++ ) {
      print_Fact( &(e->adds[i]) );
      printf("\n");
    }
    printf("\nDels\n");
    for ( i = 0; i < e->num_dels; i++ ) {
      print_Fact( &(e->dels[i]) );
      printf("\n");
    }
  }

}



void print_MixedOperator( MixedOperator *o )

{

  int i, m;
  Effect *e;
  Literal *l;

  printf("\n\n----------------Operator %s, mixed form--------------\n", 
	 o->operator->name);
 
  for ( i = 0; i < o->operator->num_vars; i++ ) {
    printf("\nx%d = %s of type ", i, gconstants[o->inst_table[i]]);
    print_type( o->operator->var_types[i] );
  }

  printf("\nPreconds:\n");
  for ( i = 0; i < o->num_preconds; i++ ) {
    print_Fact( &(o->preconds[i]) );
    printf("\n");
  }

  m = 0;
  printf("\n\nEffects:");
  for ( e = o->effects; e; e = e->next ) {
    printf("\n\neffect %d, parameters %d", m++, e->num_vars);

    for ( i = 0; i < e->num_vars; i++ ) {
      printf("\nx%d of type %s",
	     o->operator->num_vars + i, gtype_names[e->var_types[i]]);
    }
    printf("\nConditions\n");
    print_Wff( e->conditions, 0 );
    printf("\nEffect Literals");
    for ( l = e->effects; l; l = l->next ) {
      if ( l->negated ) {
	printf("\nNOT ");
      } else {
	printf("\n");
      }
      print_Fact( &(l->fact) );
    }
  }

}



void print_PseudoAction( PseudoAction *o )

{

  PseudoActionEffect *e;
  int i, m;

  printf("\n\n----------------Pseudo Action %s--------------\n", 
	 o->operator->name);

  for ( i = 0; i < o->operator->num_vars; i++ ) {
    printf("\nx%d = %s of type ", i, gconstants[o->inst_table[i]]);
    print_type( o->operator->var_types[i] );
  }

  printf("\nPreconds:\n");
  for ( i = 0; i < o->num_preconds; i++ ) {
    print_Fact( &(o->preconds[i]) );
    printf("\n");
  }

  m = 0;
  printf("\n\nEffects:");
  for ( e = o->effects; e; e = e->next ) {
    printf("\n\neffect %d", m++);
    printf("\n\nConditions\n");
    for ( i = 0; i < e->num_conditions; i++ ) {
      print_Fact( &(e->conditions[i]) );
      printf("\n");
    }
    printf("\nAdds\n");
    for ( i = 0; i < e->num_adds; i++ ) {
      print_Fact( &(e->adds[i]) );
      printf("\n");
    }
    printf("\nDels\n");
    for ( i = 0; i < e->num_dels; i++ ) {
      print_Fact( &(e->dels[i]) );
      printf("\n");
    }
  }

}



void print_Action( Action *a )

{

  ActionEffect *e;
  int i, j;

  if ( !a->norm_operator &&
       !a->pseudo_action ) {
    printf("\n\nAction REACH-GOAL");
  } else {
    printf("\n\nAction %s", a->name ); 
    for ( i = 0; i < a->num_name_vars; i++ ) {
      printf(" %s", gconstants[a->name_inst_table[i]]);
    }
  }

  printf("\n\nPreconds:\n");
  for ( i = 0; i < a->num_preconds; i++ ) {
    print_ft_name( a->preconds[i] );
    printf("\n");
  }

  printf("\n\nEffects:");
  for ( j = 0; j < a->num_effects; j++ ) {
    printf("\n\neffect %d", j);
    e = &(a->effects[j]);
    printf("\n\nConditions\n");
    for ( i = 0; i < e->num_conditions; i++ ) {
      print_ft_name( e->conditions[i] );
      printf("\n");
    }
    printf("\nAdds\n");
    for ( i = 0; i < e->num_adds; i++ ) {
      print_ft_name( e->adds[i] );
      printf("\n");
    }
    printf("\nDels\n");
    for ( i = 0; i < e->num_dels; i++ ) {
      print_ft_name( e->dels[i] );
      printf("\n");
    }
  }

}



void print_type( int t )

{

  int j;

  if ( gpredicate_to_type[t] == -1 ) {
    if ( gnum_intersected_types[t] == -1 ) {
      printf("%s", gtype_names[t]);
    } else {
      printf("INTERSECTED TYPE (");
      for ( j = 0; j < gnum_intersected_types[t]; j++ ) {
	if ( gpredicate_to_type[gintersected_types[t][j]] == -1 ) {
	  printf("%s", gtype_names[gintersected_types[t][j]]);
	} else {
	  printf("UNARY INERTIA TYPE (%s)", 
		 gpredicates[gpredicate_to_type[gintersected_types[t][j]]]);
	}
	if ( j < gnum_intersected_types[t] - 1 ) {
	  printf(" and ");
	}
      }
      printf(")");
    }
  } else {
    printf("UNARY INERTIA TYPE (%s)", gpredicates[gpredicate_to_type[t]]);
  }

}



void print_Fact( Fact *f )

{

  int j;

  if ( f->predicate == -3 ) {
    printf("GOAL-REACHED");
    return;
  }

  if ( f->predicate == -1 ) {
    printf("=(");
    for ( j=0; j<2; j++ ) {
      if ( f->args[j] >= 0 ) {
	printf("%s", gconstants[(f->args)[j]]);
      } else {
	printf("x%d", DECODE_VAR( f->args[j] ));
      }
      if ( j < 1) {
	printf(" ");
      }
    }
    printf(")");
    return;
  }

  if ( f->predicate == -2 ) {
    printf("!=(");
    for ( j=0; j<2; j++ ) {
      if ( f->args[j] >= 0 ) {
	printf("%s", gconstants[(f->args)[j]]);
      } else {
	printf("x%d", DECODE_VAR( f->args[j] ));
      }
      if ( j < 1) {
	printf(" ");
      }
    }
    printf(")");
    return;
  }
    
  printf("%s(", gpredicates[f->predicate]);
  for ( j=0; j<garity[f->predicate]; j++ ) {
    if ( f->args[j] >= 0 ) {
      printf("%s", gconstants[(f->args)[j]]);
    } else {
      printf("x%d", DECODE_VAR( f->args[j] ));
    }
    if ( j < garity[f->predicate] - 1 ) {
      printf(" ");
    }
  }
  printf(")");

}



void print_ft_name( int index )

{

  print_Fact( &(grelevant_facts[index]) );

}



void print_op_name( int index )

{

  int i;
  Action *a;


  if(index==-1)
    {
      printf("UNREACHEABLE\n");
      return;
    }
 if(index==INITIAL_ACTION)
    {
      printf("INITIAL_ACTION\n");
      return;
    }


  a= gop_conn[index].action;


  if ( !a->norm_operator &&
       !a->pseudo_action ) {
    printf("REACH-GOAL");
  } else {
    printf("%s", a->name ); 
    for ( i = 0; i < a->num_name_vars; i++ ) {
      printf(" %s", gconstants[a->name_inst_table[i]]);
    }
  }

}






/*
 * program output routines
 */









void print_plan( void )

{  

  int i;

  printf("\n\nff: found legal plan as follows");
  printf("\n\nstep ");
  for ( i = 0; i < gnum_plan_ops; i++ ) {
    printf("%4d: ", i);
    print_op_name( gplan_ops[i] );
    printf("\n     ");
  }

}

int result_to_dest( State *dest, State *source, int op )

{
	
}

void source_to_dest( State *dest, State *source )

{

  int i;

  for ( i = 0; i < source->num_F; i++ ) {
    dest->F[i] = source->F[i];
  }
  dest->num_F = source->num_F;

}

Bool do_best_first_search( void )

{
	
}

int max_ff_iter=100000;

void print_state( State S )

{

  int i;
  
  for ( i = 0; i < S.num_F; i++ ) {
    printf("\n%d ",S.F[i]);
    print_ft_name( S.F[i] );
  }

}