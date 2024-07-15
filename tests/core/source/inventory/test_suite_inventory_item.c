#include "defines.h"
#include "defines_weak.h"
#include "test_util.h"
#include "vectors.h"
#include <inventory/test_suite_inventory_item.h>

#include <inventory/item.c>

MunitResult assert_item_as__empty(Item *p_item) {
    munit_assert_ptr(
            p_item->m_item_use_handler,
            ==,
            0);
    munit_assert_ptr(
            p_item->m_item_protect_handler,
            ==,
            0);
    munit_assert_int(
            p_item->weight_per__item,
            ==,
            0);
    munit_assert_int(
            p_item->the_kind_of_item__this_item_is,
            ==,
            Item_Kind__None);
    munit_assert_int(
            p_item->item_filter_flags,
            ==,
            0);

    return MUNIT_OK;
}

void m_item_use__test(
        Item *p_item_self, 
        Entity *p_entity_user, 
        Game *p_game) {
    p_item_self->m_item_use_handler = 0;
}

void m_item_protect__test(
        Item *p_item_self, 
        Entity *p_entity_user, 
        Game *p_game,
        Hearts_Damaging_Specifier *p_hearts_damage) {
    p_item_self->m_item_protect_handler = 0;
}

TEST_FUNCTION(initialize_item_as) {
    Item item;
    initialize_item(
            &item,
            m_item_use__test,
            m_item_protect__test,
            i32_to__i32F20(1),
            Item_Kind__Arrow__Iron,
            ITEM_FILTER_FLAG__ARMOR);

    munit_assert_ptr(
            item.m_item_protect_handler,
            ==,
            m_item_protect__test);
    munit_assert_ptr(
            item.m_item_use_handler,
            ==,
            m_item_use__test);
    munit_assert_int(
            item.weight_per__item,
            ==,
            i32_to__i32F20(1));
    munit_assert_int(
            item.the_kind_of_item__this_item_is,
            ==,
            Item_Kind__Arrow__Iron);
    munit_assert_int(
            item.item_filter_flags,
            ==,
            ITEM_FILTER_FLAG__ARMOR);

    return MUNIT_OK;
}

TEST_FUNCTION(initialize_item_as__empty) {
    Item item;
    initialize_item_as__empty(
            &item);
    munit_assert_ptr(
            item.m_item_protect_handler,
            ==,
            0);
    munit_assert_ptr(
            item.m_item_use_handler,
            ==,
            0);
    munit_assert_int(
            item.weight_per__item,
            ==,
            0);
    munit_assert_int(
            item.the_kind_of_item__this_item_is,
            ==,
            0);
    munit_assert_int(
            item.item_filter_flags,
            ==,
            0);
    return MUNIT_OK;
}

TEST_FUNCTION(get_item__empty) {
    Item item__one, item__two;
    item__one = get_item__empty();
    initialize_item_as__empty(&item__two);

    munit_assert_ptr(
            item__one.m_item_protect_handler,
            ==,
            0);
    munit_assert_ptr(
            item__one.m_item_use_handler,
            ==,
            0);
    munit_assert(
            item__one.the_kind_of_item__this_item_is
            == Item_Kind__None);
    munit_assert(
            item__one.item_filter_flags
            == 0);

    munit_assert_ptr(
            item__one.m_item_protect_handler,
            ==,
            item__two.m_item_protect_handler);
    munit_assert_ptr(
            item__one.m_item_use_handler,
            ==,
            item__two.m_item_use_handler);
    munit_assert(
            item__one.the_kind_of_item__this_item_is
            == item__two.the_kind_of_item__this_item_is);
    munit_assert(
            item__one.item_filter_flags
            == item__two.item_filter_flags);

    return MUNIT_OK;
}

DEFINE_SUITE(item, 
        INCLUDE_TEST__STATELESS(initialize_item_as__empty),
        INCLUDE_TEST__STATELESS(initialize_item_as),
        INCLUDE_TEST__STATELESS(get_item__empty),
        END_TESTS)
