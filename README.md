# GraphApp
This project is an application for drawing, analyzing and processing network graphs.

## Table of Contents

- [About](#about)
- [Installation](#installation)
- [Available options](#available-options)
- [Credit](#credit)

## About

This is a complex application for working with network graphs, in which the user can specify the node index and edge weight. The application has a wide list of network graph processing capabilities, including: graph matrix construction, graph analysis, graph processing, shortest path search, critical path search, etc. The user can also save the graph to a file or print it as an image.

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
The project is currently under development. You can draw the graph (add and remove nodes and edges), print the graph and change settings (colors, day advice and warnings).

## Credit
Here you can find links to projects which I've used in GraphApp
- .ini parser [link to GitHub repository](https://github.com/metayeti/mINI/tree/master)


