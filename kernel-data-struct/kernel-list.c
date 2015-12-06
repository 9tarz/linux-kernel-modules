#include <linux/list.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
// If you are using kmalloc or kzalloc() for memory allocation you have to include linux/slab.h they are called as slab allocators, these slab are chunks i.e. "cache" present in RAM and are physically contiguous. These slab allocator use underlying "Buddy System Algorithm", buddy allocator to provide more fine-grained allocation.
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kanatip Chitavisutthivong");
MODULE_DESCRIPTION("Kernel Data Structure");
MODULE_VERSION("0.1");

static LIST_HEAD(birthday_list);

struct birthday {
	int day;
	int month;
	int year;
	struct list_head list;
};

int birthday_list_init(void)
{
	struct birthday *person;
	int i;
	for(i = 0; i < 5 ;i++) {
		person = kmalloc(sizeof(*person), GFP_KERNEL);
		person->day = 2+i;
		person->month = 8;
		person->year = 1995;
		INIT_LIST_HEAD(&person->list);
		list_add_tail(&person->list, &birthday_list);
	}

	printk(KERN_INFO "Loading Module\n");
	printk(KERN_INFO "This list be constructed\n");
	
	list_for_each_entry(person, &birthday_list, list) {
		printk(KERN_INFO "Day: %d Month: %d Year: %d\n", person->day, person->month, person->year);
	}

	return 0;
}	

void birthday_list_exit(void)
{
	struct birthday *person, *next;
	list_for_each_entry_safe(person, next, &birthday_list, list) {
		printk(KERN_INFO "Freeing node");
		list_del(&person->list);
		kfree(person);
	}
	printk(KERN_INFO "Removing Module\n");
}

module_init(birthday_list_init);
module_exit(birthday_list_exit);




