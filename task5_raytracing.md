# Computer Graphics, Task 5 - Guidelines

### PaweAszklar

### P.Aszklar@mini.pw.edu.pl

### Warsaw,June6,

## 1 Introduction

This document contains guidelines for Task 5 which consists of display-
ing a representation of a three dimensional scene in the program window.
For drawing, only library functions for colouring individual pixels and draw-
ing line segments can be used. All other functionality, described later in
this document, including scene modelling, projecting those models onto the
program window, and calculating colours of the resulting pixels needs to be
implemented by yourself. In particular, you should not use such functionality
build into 3D rendering libraries such as Direct3D and OpenGL.

## 2 Scene Modelling

Scene presented by the program will consist of several types of abstract
objects. They need to be modelled in a way that will simplify creation of
the final image. The scene may include following types of objects:

- **Shapes** — representing shapes displayed on the screen.
- **Light sources** — if present, they provide lighting for the scene. They
    are not drawn themselves, but may affect the colours of pixels on the
    surface of an object drawn on the screen.
- **Camera** — defines the position and orientation of the point of view
    from which the scene is being observed.

Creation of models for the solids, that are present in the scene, will often
require the use of points and vectors describing positions and directions in
a 3D space. Those points and vectors will often need to be expressed in and
converted between different coordinate systems. It is then vitally important
to always remember which coordinate system we are currently working in.
For the purpose of this task, we will assume that all coordinate systems
used are left-handed (e.g. for the coordinate system of the camera, the X


axis points to the right, the Y axis points upwards, and the Z axis points
towards the screen, i.e. away from the us — for reference in a right-handed
coordinate system the Z axis would point away from the screen instead).

### 2.1 Shapes

In this task the only shapes present in the scene will be spheres, each
define by position of its centre (expressed in the coordinate system of the
scene), its radius, and its material coefficients (as described in section5.2).
Bearing in mind the representation of transformations described in sec-
tion 3 , when creating the mesh, it is better to already store points **p** with
four coordinates, as follows:

```
p =
```
```




```
```
px
py
pz
1
```
```




```
### 2.2 Light sources

There are three types of light sources that can be placed in the scene.
Each light source will have its colour (usually white). Other parameters
depend on the light source type:

- **Point light** defined by its position - a point in the global coordinate
    system
- **Directional light** defined by its direction - a vector in the global
    coordinate system
- **Spot light** defined by position, direction (expressed in global coordi-
    nate system) and a coefficient describing the size of the cone of light.

Description of those parameters and how they affect the lighting in the scene
can be found in section5.1.

### 2.3 Camera

Camera describes the point-of-view (position and orientation) used to
observe the scene (i.e. how the image plane of the window is positioned in
relation to the rest of the scene). To properly display the scene on the screen
we need to transform all objects from the coordinate system of the scene (i.e.
the global coordinate system) to the coordinate system of the camera (see
section3.2)


## 3 Transformations

To represent transformations mentioned in the previous section in an
uniform manner, each three-dimensional point **p** an vector **v** needs to be
expressed using so called _affine_ , aka. _homogeneous_ , coordinates. Using this
representation, each point and vector has four elements, first three are equal
to its coordinates in 3D, and the fourth one is equal to 1 for points and 0
for vectors.

**p** = [ _px, py, pz,_ 1] _T_
**v** = [ _vx, vy, vz,_ 0] _T_
This will allow us to express all transformations as 4 × 4 matrices. Trans-
formation of a point or vector will be performed by multiplying such matrix
by a 4-element vector:
_v_ ′= _M v_

### 3.1 Transformation between coordinate systems

Transformation between two coordinate systems is expressed by a so
called _affine_ transformation matrix in the form of:

#### M =

```




```
```
a b c d
e f g h
i j k l
0 0 0 1
```
```




```
First three columns define the change of orientation of the axes. The last
column describes the shift of point of origin. This explains the choice of 1 as
the fourth coordinate for points and 0 for vectors, since coordinates of vectors
are only affected by the change in orientation of axes, the coordinates of
points however, are also modified by the translation of the origin, described
by the last column.

**3.1.1 Geometric interpretation of affine transformation**

```
Elements of affine transformation matrix can be interpreted as follows:
```
#### M =

```



```
```
Xxsrc Yxsrc Zxsrc 0 srcx
Xysrc Yysrc Zysrc 0 srcy
Xzsrc Yzsrc Zzsrc 0 srcz
0 0 0 1
```
```



```
where **X** _src_ , **Y** _src_ i **Z** _src_ define coordinates of unit vectors of the axes of
the source coordinate system expressed in destination coordinate system.
Similarly **0** _src_ describes coordinates of point of origin of the source coordinate
system expressed in the destination one.


**3.1.2 Construction of affine transformation matrix**

Construction of transformation matrix, where the axes and the origin of
the source coordinate system are given in the destination one is trivial. Often
however, we encounter the opposite case where axes **X** _dst_ , **Y** _dst_ , **Z** _dst_ and the
origin **0** _dst_ of the destination coordinate system are expressed using source
coordinates. Those can be used to construct the reverse transformation _M_ −^1 :

#### M −^1 =

```



```
```
Xxdst Yxdst Zxdst 0 dstx
Xydst Yydst Zydst 0 dsty
Xzdst Yzdst Zzdst 0 dstz
0 0 0 1
```
```



```
To calculate the desired transformation _M_ , we need to invert the above
matrix.
That matrix can be decomposed to:

```
M −^1 = T O
```
where:

#### T =

```



```
```
1 0 0 0 dstx
0 1 0 0 dsty
0 0 1 0 dstz
0 0 0 1
```
```



```
#### O =

```



```
```
Xxdst Yxdst Zdstx 0
Xydst Yydst Zdsty 0
Xzdst Yzdst Zdstz 0
0 0 0 1
```
```



```
If both coordinate systems are orthonormal (i.e. axes vectors in each are
unit length and perpendicular), then:

```
T −^1 =− T
```
```
O −^1 = OT
```
and as a result:

```
M =
```
```
(
M −^1
```
```
)− 1
= ( T O )−^1 = O −^1 T −^1 = OT (− T )
```
```
Multiplying the two matrices gives us:
```
#### M =

```




```
```
Xxdst Xdsty Xzdst − X dst · 0 dst
Yxdst Yydst Yzdst − Y dst · 0 dst
Zxdst Zydst Zdstz − Z dst · 0 dst
0 0 0 1
```
```




```
where **A** · **B** is a three-dimensional dot product of two vectors.


**3.1.3 Combinations of basic transformation**

Positioning an object (whose position and orientation is defined by a
matrix of transformation from the local coordinate system of the model to
the global coordinate system of the scene) using the above method may not
be the most convenient. Often a more intuitive approach would be to po-
sition the object using a series of basic transformations, such as rotations
around axes, and translations (shifting of position). We can easily define
affine transformation matrices for those basic operations. Combination of
those operations will be equivalent to multiplication of their respective ma-
trices.

**Rotation matrices** We will define three variants of rotation matrix, one
for rotation around each of the axes. For each the parameter _α_ will define
the angle of rotation.

```
RX ( α ) =
```
```



```
#### 1 0 0 0

```
0 cos α −sin α 0
0 sin α cos α 0
0 0 0 1
```
```



```
```
RY ( α ) =
```
```



```
```
cos α 0 sin α 0
0 1 0 0
−sin α 0 cos α 0
0 0 0 1
```
```



```
```
RZ ( α ) =
```
```



```
```
cos α −sin α 0 0
sin α cos α 0 0
0 0 1 0
0 0 0 1
```
```



```
**Translation matrix** Translation, usually represented by a translation
vector **t** = [ _tx, ty, tz_ ] _T_ , can also be expressed as an affine matrix:

```
T ( t ) =
```
```



```
```
1 0 0 tx
0 1 0 ty
0 0 1 tz
0 0 0 1
```
```



```
**Combination of transformations** Combination of a series of consecu-
tive transformations (in order first to last) _M_ 1 _,... , Mn_ can be expressed by a
single matrix _M_ obtained by multiplying matrices of those transformations
as follows:
_M_ = _Mn_ ··· _M_ 1


In that case the first transformation applied will be _M_ 1 , the second will
be _M_ 2 , etc. _Warning!_ Combination of transformation, similarly to matrix
multiplication is not commutative, and thus the order of operations is im-
portant.

### 3.2 Construction of camera (view) matrix

Camera matrix (aka. view matrix) can be created in many different ways,
depending on the parameters used to control it. In this example we will show
a formula for camera matrix defined by:

- **cPos** — position of the camera expressed as a point in the coordinate
    system of the scene
- **cTarget** — position of camera target (i.e. a point the camera is “look-
    ing at”) expressed in coordinate system of the scene
- **cUp** — auxiliary vector pointing “up” also expressed in coordinate sys-
    tem of the scene, which defines camera orientation ( _Warning!_ It should
    not be parallel to a line going through points **cPos** and **cTarget** )

Based on those parameters we can define an orthonormal local coordinate
system of the camera (expressed in the coordinate system of the scene):

```
cZ =
```
```
cTarget − cPos
∥ cTarget − cPos ∥
```
```
cX =
```
```
cUp × cZ
∥ cUp × cZ ∥
```
```
cY =
cZ × cX
∥ cZ × cX ∥
```
where **A** × **B** is a three-dimensional cross product of two vectors and∥ **A** ∥
is vectors length.
**cPos** is the origin of the camera coordinate system, and its axes are
defined by unit length perpendicular vectors **cX** , **cY** , **cZ**. Using the method
described in3.1.2we can calculate the matrix as follows:

#### M =

```




```
```
cXx cXy cXz − cX · cPos
cYx cYy cYz − cY · cPos
cZx cZy cZz − cZ · cPos
0 0 0 1
```
```




```

## 4 Ray-casting algorithm

This section will present an algorithm for drawing 3D shapes on a screen
using ray-casting. This method involves casting rays from the camera po-
sition through each pixel of the image. From all intersections of that ray
with shapes in the scene we select the closest one. Based on the position
of that intersection and the properties of the shape the ray intersected, we
can calculate the color, that should be stored in the pixel the ray was cast
through.

### 4.1 Ray construction

Ray is a half-line starting at some point **p** going in a direction defined
by some vector **v**. Rays going through the pixels of the image can be most
easily expressed in the coordinate system of the camera. Starting point for
each ray in this coordinate system will be:

```
p ′= [0 , 0 , 0 , 1] T
```
Rays going through pixels of the screen correspond to rays in the camera
coordinate system that go through a virtual rectangular window perpen-
dicular to theZaxis. Let _w_ and _h_ be width and height of the image (in
pixels) and lets assume theZaxis intersects the image in its centre (i.e.
point[ _cx, cy_ ] _T_ =

```
[
w − 1
2 ,
```
```
h − 1
2
```
]
). The distance of this window from the camera
should provide a horizontal field of view of _θ_ as illustrated in figure 1.

[
− _w_ − 21 _,_ − _h_ − 21 _, d_

```
] T
```
```
[
w − 1
2 ,
```
```
h − 1
2 , d
```
```
] T
```
```
θ d
```
```
Figure 1:Ray construction
```
```
Distance between the window and camera is equal to:
```
```
d =
w
2
```
cot
_θ_
2
For each pixel we need to determine the corresponding point in the win-
dow. Let its coordinates (in pixels) on the image be[ _x, y_ ] _T_. The correspond-


ing point on the image plane in the coordinate system of the camera is:

```
q =
```
```



```
```
x − cx
− y + cy
d
1
```
```


 , x ∈[0 , w ) , y ∈[0 , h )
```
```
From that it is easy to calculate ray direction v ′as follows:
```
```
v ′=
q − p ′
∥ q − p ′∥
```
Since the positions of the shapes and lights are defined in the coordinate
system of the scene, we need to transform the ray to it. Let _M_ be the camera
matrix. Ray in scene coordinate system is given by:

```
p = M −^1 p ′
```
```
v = M −^1 v ′
```
Inverted camera matrix can be easily calculated based on information pre-
sented in sections3.1.1,3.1.2and3.2.

### 4.2 Intersections

```
All points along ray( p , v )are given by the formula:
```
```
p t = p + t v , t ∈[0 , +∞)
```
Since all potential intersections will lie on the ray, for each intersection we
need only to know the value of parameter _t_ to calculate its position.
To find the closest intersection of the ray with scene elements, we need
to find one with the lowest positive value of _t_. Besides the value of _t_ for that
intersection it is important to remember the position of the intersection **p** _t_ ,
vector normal to the surface of the object at the intersection point **n** _t_ and
material coefficient of the intersected surface, as they will be required to
calculate the color of the pixel (see section 5 ).

**4.2.1 Intersections with a sphere**

```
Let the sphere be defined by
```
- **p** _s_ – center
- _r_ – radius.


Intersection of a ray with sphere surface must satisfy the following equation:

```
∥ p t − p s ∥=∥ p + t v − p s ∥= r
```
Squaring both sides of the equation produces:

```
( p + t v − p s )·( p + t v − p s ) = r^2
```
Equation can be expanded into:

```
t^2 + 2 t v ·( p − p p ) +∥ p − p p ∥^2 − r^2 = 0
```
If this quadratic equation has two solutions, we select the smaller value
of the two. If equation has no solutions, or solution (or one of the solutions)
is negative, the ray doesn’t intersect the sphere.
If the intersection exists and its position is **p** _t_ , the normal vector to the
sphere at that point is equal to:

```
n t =
p t − p s
∥ p t − p s ∥
```
**4.2.2 Intersections with an ellipsoid**

```
Let the ellipsoid be defined by
```
- **p** _e_ – centre
- _a, b, c_ – principal axes lengths (principal axes parallel to **X** _,_ **Y** _,_ **Z** axes
    respectively)

Intersection of a ray with ellipsoid surface must satisfy the following equation

```
( p t − p e ) TA ( p t − p e ) = ( p + t v − p e ) TA ( p + t v − p e ) = 1
```
#### A =

```




```
```
a −^2 0 0 0
0 b −^2 0 0
0 0 c −^20
0 0 0 1
```
```




```
Equation can be expanded into:

```
t^2 v TA v + t
```
```
(
d TA v + v TA d
```
```
)
+ d TA d −1 = 0
```
**d** = ( **p** − **p** _e_ )
If this quadric equation has two positive solutions, we select the smaller
t value of the two. If no positive solutions exist, the ray doesnt intersect the
ellipsoid. If the intersection exists and its position is _pt_ , the normal vector
to the ellipsoid at that point is equal to:

```
n t =
```
```
A ( p t − p e )
∥ A ( p t − p e )∥
```

### 4.3 Coloring pixels

From all found intersections of a ray with scene elements, we only need
the closest one, i.e. the one with smallest positive value of _t_. Based on the
position of the intersection, vector normal to the surface at intersection point
and surface material coefficients we can use Phong illumination model (as
described in section 5 ) to calculate the color of the pixel. If no intersection
was found, the corresponding pixel should be filled with a background color.

## 5 Phonga illumination model

What follows is an approximated model of interaction of surfaces with
light, known as Phong illumination model. It allows us to find the intensity
(color) of the light reflected by the surface at the given point in a given
direction to the observer.
The intensity is described by a three-component vector[ _r, g, b_ ] _T_ , repre-
senting red, green, and blue component of the reflected light. For the purpose
of following calculations, we assume that each component is a real value in
range of[0 _,_ 1], and vector[1 _,_ 1 _,_ 1]represents white color.
Firstly, we will introduce parameters and coefficients defining the light
sources and reflective properties of materials the surfaces are made of.

### 5.1 Light sources

Phong illumination model describes three types of light sources: point,
directional, and spot lights. Each light is described by its color. In addition
to that point light is defined by its position and illuminates objects equally
in all directions. Directional light is not attached to any given point, but
instead is defined by a direction, meaning, that for any point in the scene,
the light comes from the same direction. Spot lights are described by both
position and direction. Points illuminated the most lie on a halfline starting
from its position and going in its direction. The further the point is from
that line, the less illuminated it is by this light source.
For the _ith_ light source, let:

- **p** _i_ be light source position expressed in global coordinate system (avail-
    able only for point and spot lights)
- **d** _i_ be light source direction vector, expressed in global coordinate sys-
    tem (available only for directional and spot lights)
- I _pi_ be light source base intensity (colour — available for all light sources)
- _ri_ be spotlight focus coefficient (available only for spot lights; recom-
    mended values∼ 10 − 100 ).


### 5.2 Materials

In the Phong illumination model, the light reflected from a surface has
three components. The first one is ambient reflection which is constant, emits
equally in all directions and is independent of the relative positions of the
surface, light sources and the observer. It represents light scattered uniformly
throughout the whole scene. The second component is diffuse reflection. It
consist of light coming from the light source that is reflected by the surface
equally in all directions. The amount of light reflected depends on the angle
between the normal vector and the vector pointing to the light source. It
imitates matte surfaces. Third component, called specular reflection, where
the intensity of the emitted light is the strongest in the direction of the
oncoming light reflected of the surface. It imitates shiny surfaces.
For each different type of reflection, material of the surface should con-
tain a three-element vector of coefficients in range of[0 _,_ 1], representing the
amount of red, green, and blue light reflected by the surface. In addition,
for the specular reflection another scalar coefficient is needed, that describes
the focus of this reflection. For a given surface let:

- **k** _a_ =

```
[
kra, kag, kba
```
```
] T
be a vector of ambient reflection coefficients
```
- **k** _d_ =

```
[
krd, kgd, kbd
```
```
] T
be a vector of diffuse reflection coefficients
```
- **k** _s_ =

```
[
krs, ksg, ksb
```
```
] T
be a vector of specular reflection coefficients
```
- _m_ be specular focus coefficient

### 5.3 Calculating point color

Let us assume that we have a point **p** in global coordinates that lies on
a surface with material coefficients as described in section5.2and that the
vector normal to the surface at **p** is equal to **n**. To calculate the point colour
as observed by the camera we need to know:

- **I** _a_ - intensity (colour) of ambient light
- **p** _c_ - position of the camera in global coordinates
    Formula for the colour involves calculating the sum of ambient reflection,
and, for each light source, the diffuse and specular reflections, as follows:

```
I = I a k a +
```
```
∑
```
```
i
```
```
( k d I i max ( n · l i, 0) + k s I i max ( v · r i, 0) m )
```
where vector **v** defines a direction from the point on the surface to the
camera:
**v** =

```
p c − p
∥ p c − p ∥
```

vector **l** _i_ defines direction from the point on the surface to the _ith_ light
source:

- for point and spot lights

```
l i =
```
```
p i − p
∥ p i − p ∥
```
- for directional lights
    **l** _i_ =− **d** _i_

vector **r** _i_ is a direction the light is coming from reflected by the surface at
the given point:
**r** _i_ = 2 ( **n** · **l** _i_ ) **n** − **l** _i_

and **I** _i_ is the intensity of the light coming to the point from the _ith_ light
source:

- for point and directional lights

```
I i = I pi
```
- for spot lights
    **I** _i_ = **I** _pi_ max (− **d** _i_ · **l** _i,_ 0)


