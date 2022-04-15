#pragma once
#include "ComputeShader.h"

class BezierSurfaceTexture : public QOpenGLFunctions_4_4_Core
{
public:
	BezierSurfaceTexture();
	~BezierSurfaceTexture();

	void setBezierSize(int size);
	void setControlPoint(int size, std::vector<glm::vec4>* data);
	void computeBezierPoints();
	void computeNormal();
	void debug();

	unsigned int getBezierTexture() { return _bezierTextureID;  }
	unsigned int getNormalTexture() { return _bezierNormalTextureID; }
	unsigned int getControlPointsTexture() { return _controlPointsTextureID; }
	
private:

	void initTextures();
	
	unsigned int _bezierTextureID;
	unsigned int _bezierNormalTextureID;
	unsigned int _controlPointsTextureID;
	unsigned int _bezierTextureSize;
	unsigned int _controlPointsTextureSize;

	ComputeShader *_bezierTextureCompute;
	ComputeShader *_bezierNormalCompute;

};