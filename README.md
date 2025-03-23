# GraphApp
This project is an application for drawing, analyzing and processing network graphs.

## Table of Contents

- [About](#about)
- [Installation](#installation)
- [Available options](#available-options)
- [Credit](#credit)

## About

This is a comprehensive application for working with network graphs, in which the user can specify the node index and edge weight. The application features are focused on processing network graphs. The user can also save the graph to a file or print it as an image.

## Installation

### Prerequisites

- Installed and configured wxWidgets framework
- C++14 or above
- Microsoft Visual Studio 2019 or newer

### Steps

1. Clone the repository:
    ```bash
    git clone https://github.com/GreenHatCode/GraphApp.git
    ```
2.  Change git remote url to avoid accidental pushes to base project
    ```bash
    git remote set-url origin github_username/repo_name
    git remote -v # confirm the changes
    ```
3. Open the solution in Microsoft Visual Studio (open file GraphApp.sln)
4. Compile the project under x86, select debug or release. 

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
Here you can find links to projects which I've used in GraphApp
- .ini parser [link to GitHub repository](https://github.com/metayeti/mINI/tree/master)


