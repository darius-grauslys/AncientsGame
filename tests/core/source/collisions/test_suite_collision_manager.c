#include <collisions/test_suite_collision_manager.h>

#include <collisions/collision_manager.c>

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

    munit_assert_ptr_equal(
            collision_manager.most_north_western__node,
            &collision_manager.collision_nodes[
            get_chunk_index_during__initialization(0,
            CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS-1)]);

    Collision_Manager__Collision_Node *current_node =
        collision_manager.most_north_western__node
        ->collision_node__north;

    for (int32_t y=0;
            y<CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS;
            y++) {
        for (int32_t x=0;
                x<CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW;
                x++) {
            // check east
            munit_assert_ptr_equal(
                    current_node->collision_node__east,
                    &collision_manager.collision_nodes[
                    get_chunk_index_during__initialization(x+1,y)]
                    );
            // check west
            munit_assert_ptr_equal(
                    current_node->collision_node__west,
                    &collision_manager.collision_nodes[
                    get_chunk_index_during__initialization(x-1,y)]
                    );
            // check north
            munit_assert_ptr_equal(
                    current_node->collision_node__north,
                    &collision_manager.collision_nodes[
                    get_chunk_index_during__initialization(x,y+1)]
                    );
            // check south
            munit_assert_ptr_equal(
                    current_node->collision_node__south,
                    &collision_manager.collision_nodes[
                    get_chunk_index_during__initialization(x,y-1)]
                    );
            current_node = current_node->collision_node__east;
        }
        current_node = current_node->collision_node__north;
    }

    current_node =
        collision_manager.most_north_western__node;
    int32_t x = 0, y = 7;
    for (int32_t i = munit_rand_int_range(16,32);
            i>=0;i--) {
        int dx = munit_rand_int_range(-1,1);
        int dy = munit_rand_int_range(-1,1);
        if (dx == 1) {
            current_node = current_node->collision_node__east;
        } else if (dx == -1) {
            current_node = current_node->collision_node__west;
        }
        if (dy == 1) {
            current_node = current_node->collision_node__north;
        } else if (dy == -1) {
            current_node = current_node->collision_node__south;
        }
        x += dx;
        y += dy;
        munit_assert_ptr_equal(
                current_node,
                &collision_manager.collision_nodes[
                get_chunk_index_during__initialization(x,y)]);
    }

    munit_assert_int32(
            collision_manager.collision_nodes[0]
            .legal_directions,
            ==,
            DIRECTION__NORTH_EAST);
    munit_assert_int32(
            collision_manager.collision_nodes[
            CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW - 1]
            .legal_directions,
            ==,
            DIRECTION__NORTH_WEST);
    munit_assert_int32(
            collision_manager.collision_nodes[
            CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW * 
            (CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS - 1)]
            .legal_directions,
            ==,
            DIRECTION__SOUTH_EAST);
    munit_assert_int32(
            collision_manager.collision_nodes[
            CHUNK_MANAGER__QUANTITY_OF_CHUNKS - 1]
            .legal_directions,
            ==,
            DIRECTION__SOUTH_WEST);

    Collision_Manager__Collision_Node *collision_node__boundary;
    for (uint32_t y=1;
            y<CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS-1;
            y++) {
        collision_node__boundary =
            &collision_manager.collision_nodes[
                get_chunk_index_during__initialization(0, y)];
        munit_assert_int32(
                collision_node__boundary->
                legal_directions,
                ==,
                DIRECTION__NORTH_EAST | DIRECTION__SOUTH);
        collision_node__boundary =
            &collision_manager.collision_nodes[
                get_chunk_index_during__initialization(
                        CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW - 1, y)];
        munit_assert_int32(
                collision_node__boundary->
                legal_directions,
                ==,
                DIRECTION__NORTH_WEST | DIRECTION__SOUTH);
    }
    for (uint32_t x=1;
            x<CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW-1;
            x++) {
        collision_node__boundary =
            &collision_manager.collision_nodes[
                get_chunk_index_during__initialization(x, 0)];
        munit_assert_int32(
                collision_node__boundary->
                legal_directions,
                ==,
                DIRECTION__SOUTH_EAST | DIRECTION__WEST);
        collision_node__boundary =
            &collision_manager.collision_nodes[
                get_chunk_index_during__initialization(
                        x, CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS - 1)];
        munit_assert_int32(
                collision_node__boundary->
                legal_directions,
                ==,
                DIRECTION__NORTH_WEST | DIRECTION__EAST);
    }

    return MUNIT_OK;
}

TEST_FUNCTION(get_collision_node_for__this_position) {
    Collision_Manager collision_manager;
    init_collision_manager(&collision_manager);

    int32_t x__chunk,y__chunk;
    Collision_Manager__Collision_Node *node, *actual_node;
    for (int32_t i = munit_rand_int_range(16,32);
            i>=0;i--) {
        x__chunk = munit_rand_int_range(0, 
                CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW - 1);
        y__chunk = munit_rand_int_range(0, 
                CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS - 1);

        node =
            get_collision_node_for__this_position(
                    &collision_manager,
                    x__chunk, y__chunk);
        actual_node =
            &collision_manager.collision_nodes[
                get_chunk_index_during__initialization(
                        x__chunk,
                        y__chunk)];
        munit_assert_ptr_equal(node, actual_node);
    }

    x__chunk = -1;
    y__chunk = -1;

    node =
        get_collision_node_for__this_position(
                &collision_manager,
                x__chunk,
                y__chunk);
    munit_assert_ptr_equal(node, 0);

    x__chunk = CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW;
    y__chunk = CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS;

    node =
        get_collision_node_for__this_position(
                &collision_manager,
                x__chunk,
                y__chunk);
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

void seed_collision_manager_nodes_with__dummy_entity(
        Collision_Manager *collision_manager) {
    for (uint32_t i=0;
            i<CHUNK_MANAGER__QUANTITY_OF_CHUNKS;
            i++) {
        Collision_Manager__Collision_Node *node =
            &collision_manager->collision_nodes[i];

        for (uint32_t j=0;
                j<ENTITY_MAXIMUM_QUANTITY_OF__COLLIDABLE;
                j++) {
            // I tried taking an entity pointer by argument
            // and placing it here, but it wouldn't work.
            // Seg fault. Weird right?
            // I had the memory for that pointer on the stack
            // then in global, then on the heap and each
            // one didn't work. This does though.
            //
            // Something to do with munit or am I dumb?
            //
            // This works for a non-zero pointer value atm.
            // We don't actually want to test entity stuff
            // anyway. Not here.
            node->entity_ptrs[i] = (Entity*)collision_manager;
        }
    }
}

void assert_legal_directions(
        Collision_Manager *collision_manager,
        Direction direction_from_manager_center_to_moved_edge,
        uint32_t iterations) {
    // As we move along the moved edge
    // we first check the corner, the middle edge
    // and the other corner.
    //
    // We also check the opposite edge to make sure
    // it was correctly updated as well.
    Direction expect_legal_direction_of__start_corner;
    Direction expect_legal_direction_of__edge;
    Direction expect_legal_direction_of__end_corner;

    Direction expect_legal_direction_of__opposite_start_corner;
    Direction expect_legal_direction_of__opposite_edge;
    Direction expect_legal_direction_of__opposite_end_corner;

    // 
    // There are two nodes that were former corners
    // and are not edges, make sure they're 
    // correct as well.
    //
    Direction expect_legal_direction_of__edge_extension_one;
    Direction expect_legal_direction_of__edge_extension_two;

    Collision_Manager__Collision_Node *current_node;

    init_collision_manager(collision_manager);
    seed_collision_manager_nodes_with__dummy_entity(
            collision_manager);

    update_collision_manager__nodes_legal_directions(
            collision_manager,
            direction_from_manager_center_to_moved_edge);

    current_node =
        collision_manager->most_north_western__node;
    switch (direction_from_manager_center_to_moved_edge) {
        default:
            munit_assert_false(true);
            // Invalid arguments given.
            return;
        case DIRECTION__NORTH:
            expect_legal_direction_of__start_corner =
                DIRECTION__SOUTH_EAST;
            expect_legal_direction_of__edge =
                DIRECTION__SOUTH_EAST | DIRECTION__WEST;
            expect_legal_direction_of__end_corner =
                DIRECTION__SOUTH_WEST;

            expect_legal_direction_of__edge_extension_one =
                DIRECTION__NORTH_EAST | DIRECTION__SOUTH;
            expect_legal_direction_of__edge_extension_two =
                DIRECTION__NORTH_WEST | DIRECTION__SOUTH;

            expect_legal_direction_of__opposite_start_corner =
                DIRECTION__NORTH_EAST;
            expect_legal_direction_of__opposite_edge =
                DIRECTION__NORTH_EAST | DIRECTION__WEST;
            expect_legal_direction_of__opposite_end_corner =
                DIRECTION__NORTH_WEST;

            current_node =
                collision_manager->most_north_western__node
                ->collision_node__north;
            break;
        case DIRECTION__EAST:
            expect_legal_direction_of__start_corner =
                DIRECTION__SOUTH_WEST;
            expect_legal_direction_of__edge =
                DIRECTION__SOUTH_WEST | DIRECTION__NORTH;
            expect_legal_direction_of__end_corner =
                DIRECTION__NORTH_WEST;

            expect_legal_direction_of__edge_extension_one =
                DIRECTION__SOUTH_EAST | DIRECTION__WEST;
            expect_legal_direction_of__edge_extension_two =
                DIRECTION__NORTH_EAST | DIRECTION__WEST;

            expect_legal_direction_of__opposite_start_corner =
                DIRECTION__NORTH_EAST;
            expect_legal_direction_of__opposite_edge =
                DIRECTION__NORTH_WEST | DIRECTION__SOUTH;
            expect_legal_direction_of__opposite_end_corner =
                DIRECTION__NORTH_WEST;
            break;
        case DIRECTION__SOUTH:
            expect_legal_direction_of__start_corner =
                DIRECTION__NORTH_EAST;
            expect_legal_direction_of__edge =
                DIRECTION__NORTH_EAST | DIRECTION__WEST;
            expect_legal_direction_of__end_corner =
                DIRECTION__NORTH_WEST;

            expect_legal_direction_of__edge_extension_one =
                DIRECTION__NORTH_EAST | DIRECTION__SOUTH;
            expect_legal_direction_of__edge_extension_two =
                DIRECTION__NORTH_WEST | DIRECTION__SOUTH;

            expect_legal_direction_of__opposite_start_corner =
                DIRECTION__SOUTH_EAST;
            expect_legal_direction_of__opposite_edge =
                DIRECTION__SOUTH_EAST | DIRECTION__WEST;
            expect_legal_direction_of__opposite_end_corner =
                DIRECTION__SOUTH_WEST;
            break;
        case DIRECTION__WEST:
            expect_legal_direction_of__start_corner =
                DIRECTION__SOUTH_EAST;
            expect_legal_direction_of__edge =
                DIRECTION__SOUTH_EAST | DIRECTION__NORTH;
            expect_legal_direction_of__end_corner =
                DIRECTION__NORTH_EAST;

            expect_legal_direction_of__edge_extension_one =
                DIRECTION__SOUTH_EAST | DIRECTION__WEST;
            expect_legal_direction_of__edge_extension_two =
                DIRECTION__NORTH_EAST | DIRECTION__WEST;

            expect_legal_direction_of__opposite_start_corner =
                DIRECTION__SOUTH_EAST;
            expect_legal_direction_of__opposite_edge =
                DIRECTION__SOUTH_EAST | DIRECTION__NORTH;
            expect_legal_direction_of__opposite_end_corner =
                DIRECTION__SOUTH_WEST;

            current_node =
                collision_manager->most_north_western__node
                ->collision_node__west;
            break;
    }

    for (uint32_t i=0;i<iterations;i++) {
        for (uint32_t j=0;
                j<ENTITY_MAXIMUM_QUANTITY_OF__COLLIDABLE;
                j++) {
            munit_assert_ptr_equal(
                    current_node->entity_ptrs[j],
                    0);
        }
        if (i==0) {
            printf("\t\tChecking starting corner...\n");
            munit_assert_int32(
                    current_node->legal_directions,
                    ==,
                    expect_legal_direction_of__start_corner);
            switch (direction_from_manager_center_to_moved_edge) {
                default:
                case DIRECTION__NORTH:
                    printf("\t\t\tChecking north starting edge extension...\n");
                    munit_assert_int32(
                            current_node->collision_node__south->legal_directions,
                            ==,
                            expect_legal_direction_of__edge_extension_one);
                    printf("\t\t\tChecking north opposite corner...\n");
                    munit_assert_int32(
                            current_node->collision_node__north->legal_directions,
                            ==,
                            expect_legal_direction_of__opposite_start_corner);
                    break;
                case DIRECTION__EAST:
                    printf("\t\t\tChecking east starting edge extension...\n");
                    munit_assert_int32(
                            current_node->collision_node__west->legal_directions,
                            ==,
                            expect_legal_direction_of__edge_extension_one);
                    printf("\t\t\tChecking east opposite corner...\n");
                    munit_assert_int32(
                            current_node->collision_node__east->legal_directions,
                            ==,
                            expect_legal_direction_of__opposite_start_corner);
                    break;
                case DIRECTION__WEST:
                    printf("\t\t\tChecking west starting edge extension...\n");
                    munit_assert_int32(
                            current_node->collision_node__east->legal_directions,
                            ==,
                            expect_legal_direction_of__edge_extension_one);
                    printf("\t\t\tChecking west opposite corner...\n");
                    munit_assert_int32(
                            current_node->collision_node__west->legal_directions,
                            ==,
                            expect_legal_direction_of__opposite_start_corner);
                    break;
                case DIRECTION__SOUTH:
                    printf("\t\t\tChecking south starting edge extension...\n");
                    munit_assert_int32(
                            current_node->collision_node__north->legal_directions,
                            ==,
                            expect_legal_direction_of__edge_extension_one);
                    printf("\t\t\tChecking south opposite corner...\n");
                    munit_assert_int32(
                            current_node->collision_node__south->legal_directions,
                            ==,
                            expect_legal_direction_of__opposite_start_corner);
                    break;
            }
        } else if (
                i == CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW-1) {
            printf("Checking end corner...\n");
            munit_assert_int32(
                    current_node->legal_directions,
                    ==,
                    expect_legal_direction_of__edge);
            switch (direction_from_manager_center_to_moved_edge) {
                default:
                case DIRECTION__NORTH:
                    printf("\t\t\tChecking north ending edge extension...\n");
                    munit_assert_int32(
                            current_node->collision_node__south->legal_directions,
                            ==,
                            expect_legal_direction_of__edge_extension_two);
                    printf("\t\t\tChecking north opposite corner...\n");
                    munit_assert_int32(
                            current_node->collision_node__north->legal_directions,
                            ==,
                            expect_legal_direction_of__opposite_end_corner);
                    break;
                case DIRECTION__EAST:
                    printf("\t\t\tChecking east ending edge extension...\n");
                    munit_assert_int32(
                            current_node->collision_node__west->legal_directions,
                            ==,
                            expect_legal_direction_of__edge_extension_two);
                    printf("\t\t\tChecking east opposite corner...\n");
                    munit_assert_int32(
                            current_node->collision_node__east->legal_directions,
                            ==,
                            expect_legal_direction_of__opposite_end_corner);
                    break;
                case DIRECTION__WEST:
                    printf("\t\t\tChecking west ending edge extension...\n");
                    munit_assert_int32(
                            current_node->collision_node__east->legal_directions,
                            ==,
                            expect_legal_direction_of__edge_extension_two);
                    printf("\t\t\tChecking west opposite corner...\n");
                    munit_assert_int32(
                            current_node->collision_node__west->legal_directions,
                            ==,
                            expect_legal_direction_of__opposite_end_corner);
                    break;
                case DIRECTION__SOUTH:
                    printf("\t\t\tChecking south ending edge extension...\n");
                    munit_assert_int32(
                            current_node->collision_node__north->legal_directions,
                            ==,
                            expect_legal_direction_of__edge_extension_two);
                    printf("\t\t\tChecking south opposite corner...\n");
                    munit_assert_int32(
                            current_node->collision_node__south->legal_directions,
                            ==,
                            expect_legal_direction_of__opposite_end_corner);
                    break;
            }
        } else {
            printf("Checking edge...\n");
            munit_assert_int32(
                    current_node->legal_directions,
                    ==,
                    expect_legal_direction_of__end_corner);
            switch (direction_from_manager_center_to_moved_edge) {
                default:
                case DIRECTION__NORTH:
                    printf("\t\t\tChecking north former edge (ANY)...\n");
                    munit_assert_int32(
                            current_node->collision_node__south->legal_directions,
                            ==,
                            DIRECTION__ANY);
                    printf("\t\t\tChecking north opposite edge ...\n");
                    munit_assert_int32(
                            current_node->collision_node__north->legal_directions,
                            ==,
                            expect_legal_direction_of__opposite_edge);
                    break;
                case DIRECTION__EAST:
                    printf("\t\t\tChecking east former edge (ANY)...\n");
                    munit_assert_int32(
                            current_node->collision_node__west->legal_directions,
                            ==,
                            DIRECTION__ANY);
                    printf("\t\t\tChecking east opposite edge ...\n");
                    munit_assert_int32(
                            current_node->collision_node__east->legal_directions,
                            ==,
                            expect_legal_direction_of__opposite_edge);
                    break;
                case DIRECTION__WEST:
                    printf("\t\t\tChecking west former edge (ANY)...\n");
                    munit_assert_int32(
                            current_node->collision_node__east->legal_directions,
                            ==,
                            DIRECTION__ANY);
                    printf("\t\t\tChecking west opposite edge ...\n");
                    munit_assert_int32(
                            current_node->collision_node__west->legal_directions,
                            ==,
                            expect_legal_direction_of__opposite_edge);
                    break;
                case DIRECTION__SOUTH:
                    printf("\t\t\tChecking south former edge (ANY)...\n");
                    munit_assert_int32(
                            current_node->collision_node__north->legal_directions,
                            ==,
                            DIRECTION__ANY);
                    printf("\t\t\tChecking south opposite edge ...\n");
                    munit_assert_int32(
                            current_node->collision_node__south->legal_directions,
                            ==,
                            expect_legal_direction_of__opposite_edge);
                    break;
            }
        }
        switch (direction_from_manager_center_to_moved_edge) {
            default:
            case DIRECTION__NORTH:
            case DIRECTION__SOUTH:
                current_node =
                    current_node->collision_node__east;
                break;
            case DIRECTION__EAST:
            case DIRECTION__WEST:
                current_node =
                    current_node->collision_node__south;
                break;
        }
    }
}

TEST_FUNCTION(update_collision_manager__nodes_legal_directions) {
    Collision_Manager collision_manager;

    printf("\n\tChecking north...\n");
    assert_legal_directions(
            &collision_manager, 
            DIRECTION__NORTH, 
            CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW);
    printf("\tChecking east...\n");
    assert_legal_directions(
            &collision_manager, 
            DIRECTION__EAST,
            CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS);
    printf("\tChecking south...\n");
    assert_legal_directions(
            &collision_manager, 
            DIRECTION__SOUTH, 
            CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW);
    printf("\tChecking west...\n");
    assert_legal_directions(
            &collision_manager, 
            DIRECTION__WEST, 
            CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS);

    return MUNIT_OK;
}

TEST_FUNCTION(move_collision_manager) {
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

    move_collision_manager(
            &collision_manager,
            DIRECTION__NORTH,
            1);

    node_received =
        get_collision_node_for__this_position(
                &collision_manager,
                x__chunk, y__chunk);

    munit_assert_ptr_equal(
            node_travelled->collision_node__north, node_received);

    move_collision_manager(
            &collision_manager,
            DIRECTION__SOUTH,
            1);
    move_collision_manager(
            &collision_manager,
            DIRECTION__SOUTH,
            1);

    node_received =
        get_collision_node_for__this_position(
                &collision_manager,
                x__chunk, y__chunk);

    munit_assert_ptr_equal(
            node_travelled->collision_node__south, node_received);

    move_collision_manager(
            &collision_manager,
            DIRECTION__NORTH,
            1);
    move_collision_manager(
            &collision_manager,
            DIRECTION__EAST,
            1);

    node_received =
        get_collision_node_for__this_position(
                &collision_manager,
                x__chunk, y__chunk);

    munit_assert_ptr_equal(
            node_travelled->collision_node__east, node_received);

    move_collision_manager(
            &collision_manager,
            DIRECTION__WEST,
            1);
    move_collision_manager(
            &collision_manager,
            DIRECTION__WEST,
            1);

    node_received =
        get_collision_node_for__this_position(
                &collision_manager,
                x__chunk, y__chunk);

    munit_assert_ptr_equal(
            node_travelled->collision_node__west, node_received);

    return MUNIT_OK;
    return MUNIT_OK;
}

TEST_FUNCTION(set_collision_manager_at__position) {
    Collision_Manager collision_manager;
    init_collision_manager(&collision_manager);

    Collision_Manager__Collision_Node 
        *node_test, *node_actual;

    node_test =
        get_collision_node_for__this_position(
                &collision_manager,
                2, 2);

    set_collision_manager_at__position(
            &collision_manager,
            collision_manager.x__center_chunk,
            collision_manager.y__center_chunk + 2);

    node_actual =
        get_collision_node_for__this_position(
                &collision_manager,
                2, 2);

    munit_assert_ptr_equal(node_test, node_actual);

    set_collision_manager_at__position(
            &collision_manager,
            collision_manager.x__center_chunk,
            collision_manager.y__center_chunk + 1);

    node_actual =
        get_collision_node_for__this_position(
                &collision_manager,
                2, 2);

    munit_assert_ptr_equal(0, node_actual);

    set_collision_manager_at__position(
            &collision_manager,
            collision_manager.x__center_chunk,
            collision_manager.y__center_chunk - 3);

    node_test =
        get_collision_node_for__this_position(
                &collision_manager,
                7, 0);

    set_collision_manager_at__position(
            &collision_manager,
            collision_manager.x__center_chunk,
            collision_manager.y__center_chunk + 1);

    node_actual =
        get_collision_node_for__this_position(
                &collision_manager,
                7, 8);

    munit_assert_ptr_equal(node_test, node_actual);

    return MUNIT_OK;
}

DEFINE_SUITE(collision_manager, 
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
            (move_collision_manager),
        INCLUDE_TEST__STATELESS
            (set_collision_manager_at__position),
        INCLUDE_TEST__STATELESS
            (update_collision_manager__nodes_legal_directions),
        END_TESTS);
