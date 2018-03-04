# from matplotlib import pyplot
# from mpl_toolkits.mplot3d import Axes3D
# from plotly.graph_objs import *
from plotly.offline import download_plotlyjs, init_notebook_mode, plot, iplot
from plotly.graph_objs import Scatter, Figure, Layout, Scatter3d

class Show3D:
    def __init__(self):
        pass

    def createCuboid(self,x, y, z):
        returnX = []
        returnY = []
        returnZ = []

        firstCoord = [0, 1, 1, 0, 0]
        secondCoord = [0, 0, 1, 1, 0]
        for i in range(2):
            for j in range(5):
                returnX.append(x[firstCoord[j]])
                returnY.append(y[secondCoord[j]])
                returnZ.append(z[i])

        cnt = 1
        k = 1
        tmpZ = 1
        for j in range(3):
            for i in range(2):
                if k % 2 == 0:
                    if tmpZ == 0:
                        tmpZ = 1
                    else:
                        tmpZ = 0
                k += 1
                returnX.append(x[firstCoord[cnt]])
                returnY.append(y[secondCoord[cnt]])
                returnZ.append(z[tmpZ])
            cnt += 1
        return returnX, returnY, returnZ

    def TestShow(self,sequence_containing_x_vals,sequence_containing_y_vals,sequence_containing_z_vals):
        # fig = pyplot.figure()
        # ax = Axes3D(fig)

        # ax.set_xlim3d(-1,1)
        # ax.set_ylim3d(-1,1)
        # ax.set_zlim3d(-1,1)

        x = [min(sequence_containing_x_vals),max(sequence_containing_x_vals)]
        y = [min(sequence_containing_y_vals),max(sequence_containing_y_vals)]
        z = [min(sequence_containing_z_vals),max(sequence_containing_z_vals)]

        # for i in range(2):
        #     for j in range(2):
        #         ax.plot3D([x[i], x[i]], [y[0],y[1]],[z[j],z[j]], color="r")
        #         ax.plot3D([x[0], x[1]], [y[i],y[i]],[z[j],z[j]], color="r")
        #         ax.plot3D([x[j], x[j]], [y[i],y[i]],[z[0],z[1]], color="r")


        # ax.scatter(sequence_containing_x_vals, sequence_containing_y_vals, sequence_containing_z_vals)
        # pyplot.show()



        trace1 = Scatter3d(
            x=sequence_containing_x_vals,
            y=sequence_containing_y_vals,
            z=sequence_containing_z_vals,
            mode='markers',
            name='ryannair',
            marker=dict(
                #color='rgb(127, 127, 127)',
                size=6,
                symbol='circle',
                line=dict(
                    color='rgb(204, 204, 204)',
                    width=0.1
                ),
                opacity=1
            )
        )


        cubeX,cubeY,cubeZ = self.createCuboid(x,y,z)
        trace2 = Scatter3d(
            x=cubeX,
            y=cubeY,
            z=cubeZ,
            mode='lines',
            name='Selected planes',
        )

        data = [trace1,trace2]
        layout = Layout(

            scene=dict(
                xaxis=dict(
                    range=[-1, 1], ),
                yaxis=dict(
                    range=[-1, 1], ),
                zaxis=dict(
                    range=[-1, 1], ), ),
        )

        fig = Figure(data=data, layout=layout)
        plot(fig)