#!/usr/bin/python3

import matplotlib.pyplot as plt
import sys

def plot_res(x_coord, y_coord, cluster, fname):
    color_dict = dict({0:'brown',
                  1:'green',
                  2:'blue',
                  3: 'orange',
                  4: 'red',
                  5: 'black',
                  6: 'yellow',
                  7: 'dodgerblue'})

    colors = [color_dict[i] for i in cluster]
    fig = plt.figure()
    plt.scatter(x_coord, y_coord, c=colors, alpha=0.5)
    plt.title('Результат кластеризации')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.show()
    fig.savefig(fname+'.png')

if __name__ == "__main__":
    if len(sys.argv) == 2:
        outfile = sys.argv[1]
    else:
        print("plot.py <file name to save>\n")
        exit(0)

    inputData = (line.split(',') for line in sys.stdin)
    try:
        coor_x = []
        coord_y = []
        cluster = []
        for x,y,c in inputData:
            coor_x.append(float(x))
            coord_y.append(float(y))
            cluster.append(int(c))
        plot_res(coor_x,coord_y,cluster,outfile)
    except Exception:
        print("Unknown input data format")
    