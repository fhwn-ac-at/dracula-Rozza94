#include "graph.h"
#include <stdio.h>

void graph_build(Graph* graph, const Board* board, int die_faces) {
    if (!graph || !board || die_faces <= 0) return;

    graph->num_nodes = board->size;

    for (int i = 1; i <= board->size; i++) {
        graph->nodes[i].index = i;
        graph->nodes[i].num_neighbors = 0;

        for (int roll = 1; roll <= die_faces; roll++) {
            int next_pos = i + roll;
            if (next_pos > board->size) continue;

            // تحقق مما إذا كان هناك سلم أو ثعبان
            int final_pos = board_apply_jump(board, next_pos);

            // أضف الجار إلى القائمة
            if (graph->nodes[i].num_neighbors < MAX_NEIGHBORS) {
                graph->nodes[i].neighbors[graph->nodes[i].num_neighbors++] = final_pos;
            }
        }
    }
}

void graph_print(const Graph* graph) {
    if (!graph) return;

    printf("Graph representation of the board:\n");
    for (int i = 1; i <= graph->num_nodes; i++) {
        printf("Node %3d: ", i);
        for (int j = 0; j < graph->nodes[i].num_neighbors; j++) {
            printf("%3d ", graph->nodes[i].neighbors[j]);
        }
        printf("\n");
    }
}


