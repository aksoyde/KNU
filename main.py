from GeneticAlgorithm import GeneticAlgorithm  # Импорты модулей и алгоритма
import time
import pylab
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

startTime = time.time()


def function(x, y):     # Функция
    return -x*np.sin(np.sqrt(abs(x))) + y*np.cos(np.sqrt(abs(y)))


numberOfPopulationMembers = 1000        # стартовые значение
percentOfBestOnesToLive = 0.8
searchingSection = [-300, 300]
# Иницииализация
GA = GeneticAlgorithm(numberOfPopulationMembers, percentOfBestOnesToLive, searchingSection, function)

print("Searching approximated minimum...")
minimumValue = GA.searchMinimum(iterations=1000)
minimumPoint = GA.getArgumentsOfMinimumValue()
print("Found minimum ", minimumValue, " at point ", minimumPoint)
print("Searching time: %s seconds." % (time.time() - startTime))


def makeData ():        # Построение графика
    x = np.arange (-300, 300, 1)
    y = np.arange (-300, 300, 1)
    xgrid, ygrid = np.meshgrid(x, y)

    zgrid = 2*xgrid**2*(9-xgrid)-ygrid**2*(9*ygrid**2-4) -3*xgrid*ygrid

    return xgrid, ygrid, zgrid


x, y, z = makeData()

fig = pylab.figure()
axes = Axes3D(fig)

axes.plot_surface(x, y, z)

pylab.show()
