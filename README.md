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

## Available options
The main feature of this application is drawing and processing network graphs. You can draw a graph (add, move and delete nodes and edges) and then calculate timing parameters for each node (which represents an event), according to node indices, edge weights and graph topology. You can also print the graph using the standard printing options in your OS or save it to a file. The application has modifiable settings (colors, day tips and warnings) that the user can set in the preferences dialog.

List of available options
- draw graph
- edit the graph (move nodes, clear the drawing area and add/remove graph elements)
- load/save graph to a file (the application uses xml files to store graphs)
- graph processing
    - graph validation before processing
    - calculating: early date of event occurrence, late date of event occurrence, time reserve for each event (node)
    - printing the processing results in three possible ways: to the drawing area, to a separate window (the user can copy the results as text) and to a file
- printing of the graph using standard printer options in the user OS
- preferences dialog with various options to customize the user interface and UX of the application
- application help (provided throught tip of the day and help button in menu)


## Credit
GraphApp uses the following external project(s):
- [mINI](https://github.com/metayeti/mINI/tree/master) – Lightweight `.ini` file parser


