#include "BezierSurfaceTexture.h"

BezierSurfaceTexture::BezierSurfaceTexture()
{
	initializeOpenGLFunctions();
	_bezierTextureCompute = new ComputeShader("BezierSurfaceCompute.glsl");
	_bezierNormalCompute = new ComputeShader("normalCompute.glsl");
	initTextures();
}

BezierSurfaceTexture::~BezierSurfaceTexture()
{
}

void BezierSurfaceTexture::setBezierSize(int size)
{
	_bezierTextureSize = size;
	glBindTexture(GL_TEXTURE_2D, _bezierTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, size, size, 0, GL_RGBA, GL_FLOAT, nullptr);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _bezierNormalTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, size, size, 0, GL_RGBA, GL_FLOAT, nullptr);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void BezierSurfaceTexture::setControlPoint(int size, std::vector<glm::vec4>* data)
{
	glBindTexture(GL_TEXTURE_2D, _controlPointsTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, size, size, 0, GL_RGBA, GL_FLOAT, data->data());
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}


void BezierSurfaceTexture::computeBezierPoints()
{
	_bezierTextureCompute->use();
	_bezierTextureCompute->setInt("bezierSize", _bezierTextureSize);
	_bezierTextureCompute->setInt("ControlSize", 7);
	glBindImageTexture(0, _bezierTextureID, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
	glBindImageTexture(1, _controlPointsTextureID, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA32F);
	_bezierTextureCompute->execute(_bezierTextureSize / 16 + 1, _bezierTextureSize / 16 + 1, 1);
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}

void BezierSurfaceTexture::computeNormal()
{
	_bezierNormalCompute->use();
	glBindImageTexture(0, _bezierTextureID, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA32F);
	glBindImageTexture(1, _bezierNormalTextureID, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
	_bezierNormalCompute->execute(_bezierTextureSize / 16 + 1, _bezierTextureSize / 16 + 1, 1);
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}

void BezierSurfaceTexture::initTextures()
{
	glGenTextures(1, &_bezierTextureID);
	glGenTextures(1, &_controlPointsTextureID);
	glGenTextures(1, &_bezierNormalTextureID);

	glBindTexture(GL_TEXTURE_2D, _bezierTextureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBindTexture(GL_TEXTURE_2D, _bezierNormalTextureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBindTexture(GL_TEXTURE_2D, _controlPointsTextureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
}
