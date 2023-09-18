RCU Variants of Linked List API
===============================

Header File: <linux/rculist.h>

void INIT_LIST_HEAD_RCU(struct list_head *list);

void list_add_rcu(struct list_head *new, struct list_head *head);

void list_add_tail_rcu(struct list_head *new, struct list_head *head);

void list_del_rcu(struct list_head *entry);

list_entry_rcu(ptr, type, member);

list_for_each_entry_rcu(pos, head, member);
....
