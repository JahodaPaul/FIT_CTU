from plotly.offline import download_plotlyjs, init_notebook_mode, plot, iplot
from plotly.graph_objs import Scatter, Figure, Layout, Scatter3d

class ShowWorld:
    def __init__(self,lons,lats):
        self.lons = lons
        self.lats = lats
        self.trace1 =  dict(
                name = 'Easyjet',
                type = 'scattergeo',
                lon = self.lons,
                lat = self.lats,
                mode = 'markers',
                marker = dict(
                    color='rgb(204, 0, 0)',
                    size = 6,
                    opacity = 0.8,
                    symbol = 'cyrcle',
                )
        )

        self.data = [self.trace1]
        self.layout = {
          "geo": {
            "countrywidth": 0.5,
            "lakecolor": "rgb(127,205,255)",
            "landcolor": "rgb(255, 255, 255)",
            "lataxis": {
              "gridcolor": "rgb(102, 102, 102)",
              "gridwidth": 0.5,
              "showgrid": True
            },
            "lonaxis": {
              "gridcolor": "rgb(102, 102, 102)",
              "gridwidth": 0.5,
              "showgrid": True
            },
            "oceancolor": "rgb(127,205,255)",
            "projection": {
              "rotation": {
                "lat": 40,
                "lon": -100,
                "roll": 0
              },
              "type": "orthographic"
            },
            "showcountries": True,
            "showlakes": True,
            "showland": True,
            "showocean": True
          },
          "showlegend": False,
          "title": "Flights"
        }

    def Show(self):
        fig = Figure(data=self.data, layout=self.layout)
        plot(fig)