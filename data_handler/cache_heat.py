import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import sys

csv_data = pd.read_csv(sys.argv[1], header=None)
csv_data.plot(y=[0,1,2,3,4,5,6,7,8,9,10,11])
plt.show()


