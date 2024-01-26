#include <collisions/test_suite_collision_manager.h>

#include <collisions/collision_manager.c>

TEST_FUNCTION(get_collision_node_index_during__initialization) {
    uint32_t index = 
        CHUNK_MANAGER__QUANTITY_OF_CHUNKS - 1;
    for (int32_t y=0;
            y<CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS;
            y++) {
        for (int32_t x=CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW-1;
                x>=0;
                x--) {
            uint32_t returned_index =
                get_collision_node_index_during__initialization(x,y);
            munit_assert_uint32(returned_index, ==, index--);
        }
    }

    return MUNIT_OK;
}

TEST_FUNCTION(update_collision_manager__layer_three) {
    Collision_Manager__Layer_Two layer_two;
    Collision_Manager__Layer_Three layer_three;

    layer_two.x__center_chunk = 4;
    layer_two.y__center_chunk = 4;

    update_collision_manager__layer_three(
            &layer_three,
            &layer_two,
            DIRECTION__NORTH_EAST);

    munit_assert_int32(layer_three.x__center_chunk, ==, 
            layer_two.x__center_chunk
            + COLLISION_MANAGER__LAYER_THREE__CHUNK_CENTER_OFFSET);
    munit_assert_int32(layer_three.y__center_chunk, ==, 
            layer_two.y__center_chunk
            + COLLISION_MANAGER__LAYER_THREE__CHUNK_CENTER_OFFSET);

    update_collision_manager__layer_three(
            &layer_three,
            &layer_two,
            DIRECTION__NORTH_WEST);

    munit_assert_int32(layer_three.x__center_chunk, ==, 
            layer_two.x__center_chunk
            - COLLISION_MANAGER__LAYER_THREE__CHUNK_CENTER_OFFSET);
    munit_assert_int32(layer_three.y__center_chunk, ==, 
            layer_two.y__center_chunk
            + COLLISION_MANAGER__LAYER_THREE__CHUNK_CENTER_OFFSET);

    update_collision_manager__layer_three(
            &layer_three,
            &layer_two,
            DIRECTION__SOUTH_EAST);

    munit_assert_int32(layer_three.x__center_chunk, ==, 
            layer_two.x__center_chunk
            + COLLISION_MANAGER__LAYER_THREE__CHUNK_CENTER_OFFSET);
    munit_assert_int32(layer_three.y__center_chunk, ==, 
            layer_two.y__center_chunk
            - COLLISION_MANAGER__LAYER_THREE__CHUNK_CENTER_OFFSET);

    update_collision_manager__layer_three(
            &layer_three,
            &layer_two,
            DIRECTION__SOUTH_WEST);

    munit_assert_int32(layer_three.x__center_chunk, ==, 
            layer_two.x__center_chunk
            - COLLISION_MANAGER__LAYER_THREE__CHUNK_CENTER_OFFSET);
    munit_assert_int32(layer_three.y__center_chunk, ==, 
            layer_two.y__center_chunk
            - COLLISION_MANAGER__LAYER_THREE__CHUNK_CENTER_OFFSET);

    return MUNIT_OK;
}

static MunitResult inline 
inline_test__layer_two__center_chunks_of__quadrants(
        Collision_Manager__Layer_Two *layer_two) {
    munit_assert_int32(layer_two
            ->layer_three__top_right.x__center_chunk, ==, 
            layer_two->x__center_chunk
            + COLLISION_MANAGER__LAYER_THREE__CHUNK_CENTER_OFFSET);
    munit_assert_int32(layer_two
            ->layer_three__top_right.y__center_chunk, ==, 
            layer_two->y__center_chunk
            + COLLISION_MANAGER__LAYER_THREE__CHUNK_CENTER_OFFSET);

    munit_assert_int32(layer_two
            ->layer_three__top_left.x__center_chunk, ==, 
            layer_two->x__center_chunk
            - COLLISION_MANAGER__LAYER_THREE__CHUNK_CENTER_OFFSET);
    munit_assert_int32(layer_two
            ->layer_three__top_left.y__center_chunk, ==, 
            layer_two->y__center_chunk
            + COLLISION_MANAGER__LAYER_THREE__CHUNK_CENTER_OFFSET);

    munit_assert_int32(layer_two
            ->layer_three__bottom_right.x__center_chunk, ==, 
            layer_two->x__center_chunk
            + COLLISION_MANAGER__LAYER_THREE__CHUNK_CENTER_OFFSET);
    munit_assert_int32(layer_two
            ->layer_three__bottom_right.y__center_chunk, ==, 
            layer_two->y__center_chunk
            - COLLISION_MANAGER__LAYER_THREE__CHUNK_CENTER_OFFSET);

    munit_assert_int32(layer_two
            ->layer_three__bottom_left.x__center_chunk, ==, 
            layer_two->x__center_chunk
            - COLLISION_MANAGER__LAYER_THREE__CHUNK_CENTER_OFFSET);
    munit_assert_int32(layer_two
            ->layer_three__bottom_left.y__center_chunk, ==, 
            layer_two->y__center_chunk
            - COLLISION_MANAGER__LAYER_THREE__CHUNK_CENTER_OFFSET);

    return MUNIT_OK;
}

TEST_FUNCTION(update_collision_manager__layer_two) {
    Collision_Manager manager;
    Collision_Manager__Layer_Two layer_two;

    manager.x__center_chunk = 4;
    manager.y__center_chunk = 4;

    MunitResult result;

    update_collision_manager__layer_two(
            &layer_two,
            &manager,
            DIRECTION__NORTH_EAST);

    munit_assert_int32(layer_two.x__center_chunk, ==, 6);
    munit_assert_int32(layer_two.y__center_chunk, ==, 6);

    result =
        inline_test__layer_two__center_chunks_of__quadrants(
                &layer_two);
    if (result != MUNIT_OK)
        return result;

    update_collision_manager__layer_two(
            &layer_two,
            &manager,
            DIRECTION__NORTH_WEST);

    munit_assert_int32(layer_two.x__center_chunk, ==, 2);
    munit_assert_int32(layer_two.y__center_chunk, ==, 6);

    result =
        inline_test__layer_two__center_chunks_of__quadrants(
                &layer_two);
    if (result != MUNIT_OK)
        return result;

    update_collision_manager__layer_two(
            &layer_two,
            &manager,
            DIRECTION__SOUTH_EAST);

    munit_assert_int32(layer_two.x__center_chunk, ==, 6);
    munit_assert_int32(layer_two.y__center_chunk, ==, 2);

    result =
        inline_test__layer_two__center_chunks_of__quadrants(
                &layer_two);
    if (result != MUNIT_OK)
        return result;

    update_collision_manager__layer_two(
            &layer_two,
            &manager,
            DIRECTION__SOUTH_WEST);

    munit_assert_int32(layer_two.x__center_chunk, ==, 2);
    munit_assert_int32(layer_two.y__center_chunk, ==, 2);

    result =
        inline_test__layer_two__center_chunks_of__quadrants(
                &layer_two);
    if (result != MUNIT_OK)
        return result;

    return MUNIT_OK;
}

TEST_FUNCTION(init_collision_manager__layer_three) {
    Collision_Manager__Layer_Three layer_three;
    Collision_Manager collision_manager;

    layer_three.x__center_chunk = 1;
    layer_three.y__center_chunk = 7;

    init_collision_manager__layer_three(
            &layer_three,
            &collision_manager);

    munit_assert_ptr_equal(
            layer_three.collision_node__top_left,
            &collision_manager.collision_nodes[0]);
    munit_assert_ptr_equal(
            layer_three.collision_node__top_right,
            &collision_manager.collision_nodes[1]);
    munit_assert_ptr_equal(
            layer_three.collision_node__bottom_left,
            &collision_manager.collision_nodes[
                CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW]);
    munit_assert_ptr_equal(
            layer_three.collision_node__bottom_right,
            &collision_manager.collision_nodes[
                CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW + 1]);

    layer_three.x__center_chunk = 7;
    layer_three.y__center_chunk = 7;

    init_collision_manager__layer_three(
            &layer_three,
            &collision_manager);

    munit_assert_ptr_equal(
            layer_three.collision_node__top_left,
            &collision_manager.collision_nodes[
            CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW - 2]);
    munit_assert_ptr_equal(
            layer_three.collision_node__top_right,
            &collision_manager.collision_nodes[
            CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW - 1]);
    munit_assert_ptr_equal(
            layer_three.collision_node__bottom_left,
            &collision_manager.collision_nodes[
                CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
                + CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW - 2]);
    munit_assert_ptr_equal(
            layer_three.collision_node__bottom_right,
            &collision_manager.collision_nodes[
                CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
                + CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW - 1]);

    return MUNIT_OK;
}

// unless init_collision_manager__layer_two makes use
// of other function calls than those already tested
// there isn't much need to test this.
TEST_FUNCTION(init_collision_manager__layer_two) {
    return MUNIT_OK;
}

TEST_FUNCTION(init_collision_manager) {
    Collision_Manager collision_manager;
    init_collision_manager(&collision_manager);

    Collision_Manager__Collision_Node *current_node =
        &collision_manager.collision_nodes[
        get_collision_node_index_during__initialization(0,0)];
    int32_t x = 0, y = 0;
    for (int32_t i = munit_rand_int_range(16,32);
            i>=0;i--) {
        int dx = munit_rand_int_range(-1,1);
        int dy = munit_rand_int_range(-1,1);
        if (dx == 1) {
            current_node = current_node->collision_node__east;
            x = (x + 1) % CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW;
        } else if (dx == -1) {
            current_node = current_node->collision_node__west;
            x = (x + (CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW - 1))
                % CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW;
        }
        if (dy == 1) {
            current_node = current_node->collision_node__north;
            y = (y + 1) % CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS;
        } else if (dy == -1) {
            current_node = current_node->collision_node__south;
            y = (y + (CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS - 1))
                % CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS;
        }
        munit_assert_ptr_equal(
                current_node,
                &collision_manager.collision_nodes[
                get_collision_node_index_during__initialization(x,y)]);
    }
    return MUNIT_OK;
}

TEST_FUNCTION(get_collision_node_for__this_position) {
    Collision_Manager collision_manager;
    init_collision_manager(&collision_manager);

    int32_t x__chunk,y__chunk;
    int32_t x__chunk_clamped,y__chunk_clamped;
    Collision_Manager__Collision_Node *node, *actual_node;
    for (int32_t i = munit_rand_int_range(16,32);
            i>=0;i--) {
        x__chunk = munit_rand_int_range(0, 
                CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW - 1);
        y__chunk = munit_rand_int_range(0, 
                CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS - 1);
        x__chunk_clamped = x__chunk;
        y__chunk_clamped = y__chunk;
        if (x__chunk_clamped < 0) {
            x__chunk_clamped = 0;
        } else if 
            (x__chunk_clamped >= CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW) {
            x__chunk_clamped =
                CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW - 1;
        }
        if (y__chunk_clamped < 0) {
            y__chunk_clamped = 0;
        } else if 
            (y__chunk_clamped >= CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS) {
            y__chunk_clamped =
                CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS - 1;
        }

        *node =
            get_collision_node_for__this_position(
                    &collision_manager,
                    x__chunk, y__chunk);
        *actual_node =
            &collision_manager.collision_nodes[
                get_collision_node_index_during__initialization(
                        x__chunk_clamped,
                        y__chunk_clamped)];
        munit_assert_ptr_equal(node, actual_node);
    }

    x__chunk = -1;
    y__chunk = -1;

    *node =
        &collision_manager.collision_nodes[
            get_collision_node_index_during__initialization(
                    x__chunk,
                    y__chunk)];
    munit_assert_ptr_equal(node, 0);

    x__chunk = CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW;
    y__chunk = CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS;

    *node =
        &collision_manager.collision_nodes[
            get_collision_node_index_during__initialization(
                    x__chunk,
                    y__chunk)];
    munit_assert_ptr_equal(node, 0);

    return MUNIT_OK;
}

TEST_FUNCTION(remove_entity_from__collision_node) {
    Entity entity;
    Collision_Manager__Collision_Node collision_node;
    init_collision_manager__collision_node(&collision_node);
    collision_node.entity_ptrs[0] = &entity;

    remove_entity_from__collision_node(
            &collision_node,
            &entity);
    munit_assert_ptr_equal(
            collision_node.entity_ptrs[0], 0);

    Entity entity_a, entity_b;
    collision_node.entity_ptrs[0] = &entity_a;
    collision_node.entity_ptrs[1] = &entity_b;
    remove_entity_from__collision_node(
            &collision_node,
            &entity_a);
    munit_assert_ptr_equal(
            collision_node.entity_ptrs[1], 0);
    munit_assert_ptr_equal(
            collision_node.entity_ptrs[0], &entity_b);
    return MUNIT_OK;
}

TEST_FUNCTION(add_entity_to__collision_node) {
    Collision_Manager__Collision_Node collision_node;
    init_collision_manager__collision_node(&collision_node);
    Entity entity;

    add_entity_to__collision_node(
            &collision_node,
            &entity);

    munit_assert_ptr_equal(
            collision_node.entity_ptrs[0], 
            &entity);
    
    add_entity_to__collision_node(
            &collision_node,
            &entity);

    munit_assert_ptr_equal(
            collision_node.entity_ptrs[0], 
            &entity);
    munit_assert_ptr_equal(
            collision_node.entity_ptrs[1], 
            0);

    return MUNIT_OK;
}

TEST_FUNCTION(add_entity_to__collision_manager) {
    Collision_Manager collision_manager;
    init_collision_manager(&collision_manager);
    Entity entity;

    entity.hitbox.x__chunk = munit_rand_int_range(
            collision_manager.x__center_chunk
            - CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW / 2, 
            collision_manager.x__center_chunk
            + CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW / 2 - 1);
    entity.hitbox.y__chunk = munit_rand_int_range(
            collision_manager.x__center_chunk
            - CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW / 2, 
            collision_manager.x__center_chunk
            + CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW / 2 - 1);

    add_entity_to__collision_manager(
            &collision_manager,
            &entity);

    Collision_Manager__Collision_Node *collision_node =
        get_collision_node_for__this_position(
                &collision_manager,
                entity.hitbox.x__chunk,
                entity.hitbox.y__chunk);

    munit_assert_ptr_equal(
            collision_node->entity_ptrs[0], 
            &entity);

    return MUNIT_OK;
}

TEST_FUNCTION(remove_entity_from__collision_manager__at) {
    Collision_Manager collision_manager;
    init_collision_manager(&collision_manager);
    Entity entity;

    entity.hitbox.x__chunk = munit_rand_int_range(
            collision_manager.x__center_chunk
            - CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW / 2, 
            collision_manager.x__center_chunk
            + CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW / 2 - 1);
    entity.hitbox.y__chunk = munit_rand_int_range(
            collision_manager.x__center_chunk
            - CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW / 2, 
            collision_manager.x__center_chunk
            + CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW / 2 - 1);

    add_entity_to__collision_manager(
            &collision_manager,
            &entity);

    Collision_Manager__Collision_Node *collision_node =
        get_collision_node_for__this_position(
                &collision_manager,
                entity.hitbox.x__chunk,
                entity.hitbox.y__chunk);

    munit_assert_ptr_equal(
            collision_node->entity_ptrs[0], 
            &entity);

    remove_entity_from__collision_manager__at(
            &collision_manager,
            &entity,
            entity.hitbox.x__chunk,
            entity.hitbox.y__chunk);

    munit_assert_ptr_equal(
            collision_node->entity_ptrs[0], 
            0);

    return MUNIT_OK;
}

TEST_FUNCTION(move_collision_manager__nodes) {
    // 
    // Note with this test, the layers do
    // not have their (x/y)__center_chunk values
    // updated, so when we call get_collision_node_for__this_position(...)
    // we will receive nodes based on old (x/y)__center_chunk values.
    //
    Collision_Manager collision_manager;
    init_collision_manager(&collision_manager);

    Collision_Manager__Collision_Node 
        *node_travelled, *node_received;

    int32_t x__chunk = 0, y__chunk = 0;
    for (int32_t i = munit_rand_int_range(16,32);
            i>=0;i--) {
        int dx__chunk = munit_rand_int_range(-1,1);
        int dy__chunk = munit_rand_int_range(-1,1);
        if (dx__chunk == 1) {
            node_travelled = node_travelled->collision_node__east;
            x__chunk = (x__chunk + 1) % CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW;
        } else if (dx__chunk == -1) {
            node_travelled = node_travelled->collision_node__west;
            x__chunk = (x__chunk + (CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW - 1))
                % CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW;
        }
        if (dy__chunk == 1) {
            node_travelled = node_travelled->collision_node__north;
            y__chunk = (y__chunk + 1) % CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS;
        } else if (dy__chunk == -1) {
            node_travelled = node_travelled->collision_node__south;
            y__chunk = (y__chunk + (CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS - 1))
                % CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS;
        }
    }

    node_travelled =
        get_collision_node_for__this_position(
                &collision_manager,
                x__chunk, y__chunk);

    move_collision_manager__nodes(
            &collision_manager,
            DIRECTION__NORTH);

    node_received =
        get_collision_node_for__this_position(
                &collision_manager,
                x__chunk, y__chunk);

    munit_assert_ptr_equal(
            node_travelled->collision_node__north, node_received);

    move_collision_manager__nodes(
            &collision_manager,
            DIRECTION__SOUTH);
    move_collision_manager__nodes(
            &collision_manager,
            DIRECTION__SOUTH);

    node_received =
        get_collision_node_for__this_position(
                &collision_manager,
                x__chunk, y__chunk);

    munit_assert_ptr_equal(
            node_travelled->collision_node__south, node_received);

    move_collision_manager__nodes(
            &collision_manager,
            DIRECTION__NORTH);
    move_collision_manager__nodes(
            &collision_manager,
            DIRECTION__EAST);

    node_received =
        get_collision_node_for__this_position(
                &collision_manager,
                x__chunk, y__chunk);

    munit_assert_ptr_equal(
            node_travelled->collision_node__east, node_received);

    move_collision_manager__nodes(
            &collision_manager,
            DIRECTION__WEST);
    move_collision_manager__nodes(
            &collision_manager,
            DIRECTION__WEST);

    node_received =
        get_collision_node_for__this_position(
                &collision_manager,
                x__chunk, y__chunk);

    munit_assert_ptr_equal(
            node_travelled->collision_node__west, node_received);

    return MUNIT_OK;
}

TEST_FUNCTION(set_collision_manager__center_chunk) {
    Collision_Manager collision_manager;
    init_collision_manager(&collision_manager);

    Collision_Manager__Collision_Node 
        *node_travelled, *node_received;

    node_travelled =
        collision_manager.most_north_western__node
        ->collision_node__north;

    int32_t x__chunk = 0, y__chunk = 0;
    for (int32_t i = munit_rand_int_range(16,32);
            i>=0;i--) {
        int dx__chunk = munit_rand_int_range(-1,1);
        int dy__chunk = munit_rand_int_range(-1,1);
        if (dx__chunk == 1) {
            node_travelled = node_travelled->collision_node__east;
            x__chunk = (x__chunk + 1) % CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW;
        } else if (dx__chunk == -1) {
            node_travelled = node_travelled->collision_node__west;
            x__chunk = (x__chunk + (CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW - 1))
                % CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW;
        }
        if (dy__chunk == 1) {
            node_travelled = node_travelled->collision_node__north;
            y__chunk = (y__chunk + 1) % CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS;
        } else if (dy__chunk == -1) {
            node_travelled = node_travelled->collision_node__south;
            y__chunk = (y__chunk + (CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS - 1))
                % CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS;
        }
    }

    set_collision_manager__center_chunk(
            &collision_manager,
            collision_manager.x__center_chunk,
            collision_manager.y__center_chunk + 2);

    node_received =
        get_collision_node_for__this_position(
                &collision_manager,
                x__chunk, y__chunk);
    int64_t index_travelled = 
        ((int64_t)node_travelled 
         - (int64_t)collision_manager.collision_nodes) 
        / sizeof(Collision_Manager__Collision_Node);
    int64_t index_received = 
        ((int64_t)node_received 
         - (int64_t)collision_manager.collision_nodes) 
        / sizeof(Collision_Manager__Collision_Node);
    printf("\nindex traveled: %d, %d\n",
            index_travelled % CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW,
            index_travelled / CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW);
    printf("index received: %d, %d\n",
            index_received % CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW,
            index_received / CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW);
            

    // munit_assert_ptr_equal(
    //         node_travelled->collision_node__west->collision_node__west->collision_node__west, node_received);
    munit_assert_ptr_equal(node_travelled, node_received);
    munit_assert_false(true); // everything above is totally wrong :)

    return MUNIT_OK;
}

DEFINE_SUITE(collision_manager, 
        INCLUDE_TEST__STATELESS
            (get_collision_node_index_during__initialization), 
        INCLUDE_TEST__STATELESS
            (update_collision_manager__layer_three), 
        INCLUDE_TEST__STATELESS
            (update_collision_manager__layer_two), 
        INCLUDE_TEST__STATELESS
            (init_collision_manager__layer_three),
        INCLUDE_TEST__STATELESS
            (init_collision_manager),
        INCLUDE_TEST__STATELESS
            (get_collision_node_for__this_position),
        INCLUDE_TEST__STATELESS
            (remove_entity_from__collision_node),
        INCLUDE_TEST__STATELESS
            (add_entity_to__collision_node),
        INCLUDE_TEST__STATELESS
            (add_entity_to__collision_manager),
        INCLUDE_TEST__STATELESS
            (remove_entity_from__collision_manager__at),
        INCLUDE_TEST__STATELESS
            (move_collision_manager__nodes),
        INCLUDE_TEST__STATELESS
            (set_collision_manager__center_chunk),
        END_TESTS);
