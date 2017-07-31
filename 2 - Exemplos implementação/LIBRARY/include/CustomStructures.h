#ifndef STRUCTURES_H
#define STRUCTURES_H

//STANDARD INCLUDES
#include <vector>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/point_representation.h>
#include <pcl/search/search.h>

//-------------TYPE DEFINITIONS------------
typedef pcl::PointXYZ PXYZ;
typedef pcl::PointXYZRGB PXYZRGB;
typedef pcl::PointXYZRGBA PXYZRGBA;

typedef pcl::PointCloud<PXYZ> XYZCloud;
typedef pcl::PointCloud<PXYZRGB> XYZRGBCloud;
typedef pcl::PointCloud<PXYZRGBA> XYZRGBACloud;
typedef pcl::PointCloud<pcl::Normal> NormalCloud;
typedef pcl::PointCloud<pcl::PointNormal> PointNormalCloud;

typedef pcl::PointCloud<PXYZ>::Ptr XYZCloud_ptr;
typedef pcl::PointCloud<PXYZRGB>::Ptr XYZRGBCloud_ptr;
typedef pcl::PointCloud<PXYZRGBA>::Ptr XYZRGBACloud_ptr;
typedef pcl::PointCloud<pcl::Normal>::Ptr NormalCloud_ptr;
typedef pcl::PointCloud<pcl::PointNormal>::Ptr PointNormalCloud_ptr;

//template class pcl::PointCloud <PXYZ> ;
//template class pcl::PointCloud <PXYZRGB> ;
//template class pcl::PointCloud <PXYZRGBA> ;

typedef pcl::search::Search<PXYZ>::Ptr SearchXYZ_ptr;
typedef pcl::search::Search<PXYZRGB>::Ptr SearchXYZRGB_ptr;
typedef pcl::search::Search<PXYZRGBA>::Ptr SearchXYZRGBA_ptr;
typedef pcl::search::Search<pcl::Normal>::Ptr SearchNormal_ptr;

typedef std::vector<pcl::PointIndices> PIndicesVector;


//------------- DATA STRUCTURES -----------

typedef struct Coord2D {
	float x, y;
	Coord2D() {};
	Coord2D(float x, float y) {
		this->x = x;
		this->y = y;
	}
} Coord2D;

typedef struct Coord3D {
	float x, y, z;
	float r,g,b,a;
	Coord3D() {
		this->x = 0;
		this->y = 0;
        this->z = 0;
        this->r = 0;
        this->g = 0;
        this->b = 0;
        this->a = 0;
	};
	Coord3D(float x, float y, float z) {
		this->x = x;
		this->y = y;
        this->z = z;
        this->r = 0;
        this->g = 0;
        this->b = 0;
        this->a = 0;
	}
	Coord3D(float x, float y, float z, float r, float g, float b, float a) {
		this->x = x;
		this->y = y;
        this->z = z;
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
	}
} Coord3D;

typedef struct Cone {
	float base, height, slices,stacks;
	Cone() {
		this->base = 0;
		this->height = 0;
		this->slices = 0;
		this->stacks = 0;
	};
	Cone(float base, float height, float slices, float stacks) {
		this->base = base;
		this->height = height;
		this->slices = slices;
		this->stacks = stacks;
	}
} Cone;


typedef struct Dimension2D {
	float largura, altura;
	Dimension2D() {};
	Dimension2D(float altura, float largura) {
		this->largura = largura;
		this->altura = altura;
	}
} Dimension2D;

typedef struct Dimension3D {
	float width, height, depth;
	Dimension3D() {};
	Dimension3D(float width, float height,float depth) {
		this->width = width;
		this->height = height;
        this->depth = depth;
	}
} Dimension3D;

typedef struct Color {
	float r, g, b, a;
	Color() {
        this->r = 0;
		this->g = 0;
		this->b = 0;
		this->a = 0;
	};
	Color(float r, float g, float b, float a) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
} Color;

typedef struct Cilinder {
	float baseRadius, topRadius, height,slices,stacks;
	Cilinder() {
		this->baseRadius = 0;
		this->topRadius = 0;
		this->height = 0;
		this->slices = 0;
		this->stacks = 0;
	};
	Cilinder(float baseRadius, float topRadius, float height, float slices, float stacks) {
		this->baseRadius = baseRadius;
		this->topRadius = topRadius;
		this->height = height;
		this->slices = slices;
		this->stacks = stacks;
	}
} Cilinder;

#endif
