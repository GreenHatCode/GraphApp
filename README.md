# GraphApp
GraphApp is a desktop application for drawing, analyzing, and processing network graphs. It provides a visual and interactive interface for working with graph structures, calculating timing parameters, and customizing the layout and display.

## Table of Contents

- [About](#about)
- [Installation](#installation)
- [Available options](#available-options)
- [Credit](#credit)

## About

GraphApp is a feature-rich application for working with network graphs, where users can assign indices to nodes and set weights for edges. It supports visual editing, automatic graph analysis, and exporting of results. Users can save their work, export graphs as images, and customize the interface.

## Installation

### Prerequisites

- C++14 or newer
- [wxWidgets](https://wxwidgets.org/) (installed and configured)
- CMake 3.14 or newer
- A supported C++ compiler:
  - On Windows: Microsoft Visual Studio 2019 or newer
  - On Linux/macOS: GCC/Clang

### Build Instructions

1. Clone the repository:
    ```bash
    git clone https://github.com/GreenHatCode/GraphApp.git
    cd GraphApp
    ```
2.  Change git remote url to avoid accidental pushes to base project
    ```bash
    git remote set-url origin github_username/repo_name
    git remote -v # confirm the changes
    ```
3. Create a build directory and run CMake
    ```bash
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```
4. Run the application.

   The compiled executable can be found in the build directory, depending on your platform and configuration.

## Available Options

GraphApp is a powerful application for drawing, editing, analyzing, and exporting network graphs. It offers a wide variety of tools to manipulate graph structure, perform computations, and customize user experience. Below is a detailed list of features and options available in the application:

### Graph Editing

- **Add/Edit/Delete nodes and edges** directly on the canvas.
- **Move nodes** freely in the drawing area.
- **Context menus**:
  - On empty area: *Add Node*
  - On node: *Edit Node*, *Delete Node*
  - On edge: *Edit Edge*, *Turn Around Edge*, *Delete Edge*
- **New Add Edge Dialog** – Quickly create edges between distant nodes via a dialog, with dropdowns for node selection and edge weight input.
- **Clear drawing area** to reset the canvas.

### File Handling

- **Load/Save graphs** using XML-based project files.
- Show the **current filename in the app title bar** for better context.
- Export graph as **image** or send to printer via standard OS print dialog.

### Graph Processing

GraphApp supports advanced graph analysis with configurable options:

- **Timing analysis for events (nodes)**:
  - Early and late occurrence dates
  - Time reserve (slack)
- **Critical path highlighting**
- **Complexity factor** calculation
- **Dynamic update** of calculation results: Auto-recalculate parameters when the graph is modified (toggle in preferences)
- **Preserve previous parameter selection** across processing sessions
- **Clear calculation results**: One-click reset of visual and computed graph data

### Algorithms and Calculations

Available under the **Build** tab:

- **Adjacency Matrix** – Shows node connectivity
- **Incidence Matrix** – Edge incidence on nodes
- **Kirchhoff Matrix** – Useful for electrical/network graph properties
- **Shortest Path (Dijkstra)** – Between two selected nodes
- **Shortest Path (Bellman–Ford)** – From lowest-index node to all reachable nodes

All matrix outputs appear in a dialog with copyable text format.

### Graph Layouts

Automatically arrange nodes using:

- **Circular layout** – Evenly spaced nodes around a circle
- **Tree layout** – Hierarchical top-down or left-right placement for structured views

### Preferences & Customization

Accessible via the **Preferences Dialog**:

- Customize colors, UI behavior, and warnings
- Enable/disable **dynamic result updating**
- Store and manage previously used processing settings

### Help and Guidance

- **Tip of the Day** on startup
- Help menu with:
  - **Node Structure Info** – Visual breakdown of node fields and layout
  - Access to documentation and contextual explanations

## Credit
GraphApp uses the following external project(s):
- [mINI](https://github.com/metayeti/mINI/tree/master) – Lightweight `.ini` file parser


