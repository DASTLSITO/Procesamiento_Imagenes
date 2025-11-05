# Procesamiento de Imágenes - Qt + OpenCV

Proyecto multiplataforma para procesamiento de imágenes usando Qt y OpenCV.

## 📋 Requisitos Previos

### Para todos los sistemas:
- **Git** - Control de versiones
- **CMake 3.16+** - Sistema de build
- **Qt 5.15+ o Qt 6.2+** - Framework de aplicaciones
- **Compilador C++17** - g++, clang, o MSVC
- **OpenCV 4.5+** - Biblioteca de visión por computadora

---96+*-

## 🛠 Instalación de Dependencias

### 1. CMake - Instalación

#### Linux (Debian/Ubuntu):

```
sudo apt update
sudo apt install cmake cmake-qt-gui
```

#### Windows:
##### Con chocolatey:
``` 
choco install cmake --installargs 'ADD_CMAKE_TO_PATH=System'
```

##### Desde la pagina oficial: <a href="https://cmake.org/download/">cmake.org</a>


#### macOS:
```
brew install cmake
```

##### Verificar CMake:
```
cmake --version
```

### 2. Qt - Instalación

#### Linux (Debian/Ubuntu):

```
sudo apt install qt6-base-dev qt6-tools-dev-tools
```

#### Windows:

##### Desde la pagina oficial: <a href="https://www.qt.io/download">qt.io</a>


#### macOS:
```
brew install qt
```

### 3. Qt - OpenCV

#### Linux (Debian/Ubuntu):

```
sudo apt install libopencv-dev

# Verificar si está instalado:
pkg-config --modversion opencv4
```

#### Windows:

##### 1. Descargar OpenCV 4.10 desde <a href="https://opencv.org/releases/">opencv.org/releases</a>


##### 2. Extraer en "C:\opencv"
##### 3. Configurar variable de entorno:
```
setx OpenCV_DIR "C:\opencv\build"
```

#### macOS:
```
brew install opencv
```


### 3. 🚀 Configuración Rápida del Proyecto

Clonar, abrir el proyecto con QT y ejecutarlo! :)
