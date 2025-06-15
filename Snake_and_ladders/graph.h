#pragma once

#include "board.h"

#define MAX_NEIGHBORS 6  // أقصى عدد انتقالات مباشرة (عبر النرد 1-6)

/**
 * Represents a node (square) on the game board.
 * Each node has an index and a list of reachable neighbors (after applying jump).
 */
typedef struct {
    int index;                    // رقم المربع (مثلاً: 1, 2, ..., 100)
    int neighbors[MAX_NEIGHBORS]; // المربعات التي يمكن الوصول إليها من هنا
    int num_neighbors;           // عدد الجيران الفعلي
} GraphNode;

/**
 * Represents the full graph of the board.
 */
typedef struct {
    GraphNode nodes[MAX_BOARD_SIZE + 1];  // المربعات من 1 إلى size (index يبدأ من 1)
    int num_nodes;
} Graph;

/**
 * Initializes the graph based on the board configuration and die faces.
 * Adds edges representing legal moves (بما في ذلك الثعابين والسلالم).
 * 
 * @param graph Pointer to the graph to initialize.
 * @param board The board structure (dimensions + snakes/ladders).
 * @param die_faces Number of faces of the die (e.g., 6).
 */
void graph_build(Graph* graph, const Board* board, int die_faces);

/**
 * Prints the graph structure (for debugging).
 * @param graph Pointer to the graph.
 */
void graph_print(const Graph* graph);
