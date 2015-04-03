
#include "sprite.h";


//COMMON FUNCTIONS --TODO, MOVE TO COMMON FUNC.CPP
double Common_Round(double num)	{
	return (num > 0.0) ? floor(num + 0.5) : ceil(num - 0.5);
}



//RENDER SPRITE INITIALIZER
Sprite::Sprite(Point Position, float cScale, bool isNormalized) : _vC(0), Position(Position), Scale(cScale), _iN(isNormalized), PixelsPerSecond(1.0f), _collisionObjId(-1), CollisionField(_CollisionFieldObject())	{
	CollisionField.Type = SpriteType::RECT;
	CollisionField.BottomLeft = Position;
	CollisionField.TopRight = Position;
}
Sprite::~Sprite()	{

}


Point Sprite::_scaleMoveToFrame(Point p)	{
	return Point(p.X * (float)FrameTimeElapsed * PixelsPerSecond, p.Y * (float)FrameTimeElapsed * PixelsPerSecond);
}
void Sprite::MoveTo(Point NewPoint)	{
	float aXD = NewPoint.X - Position.X;
	float aYD = NewPoint.Y - Position.Y;
	Position = NewPoint;
	CollisionField.BottomLeft.X += aXD;
	CollisionField.TopRight.X += aXD;
	CollisionField.BottomLeft.Y += aYD;
	CollisionField.TopRight.Y += aYD;
	for (size_t i = 0; i < Children.size(); i++)	{
		Children[i].MoveTo(NewPoint);
	}
	_UpdateList();
}void Sprite::Move(Point OffsetPoint)	{
	Point tP = _scaleMoveToFrame(OffsetPoint);
	Position.X += tP.X;
	CollisionField.BottomLeft.X += tP.X;
	CollisionField.TopRight.X += tP.X;
	Position.Y += tP.Y;
	CollisionField.BottomLeft.Y += tP.Y;
	CollisionField.TopRight.Y += tP.Y;
	for (size_t i = 0; i < Children.size(); i++)	{
		Children[i].Move(OffsetPoint);
	}
	_UpdateList();
}

void Sprite::SetScale(float nScale)	{
	Scale = nScale;
	for (size_t i = 0; i < Children.size(); i++)	{
		Children[i].SetScale(nScale);
	}
	_UpdateList();
}


void Sprite::SetColor(Color C)	{
	_dC= C;
	for (size_t i = 0; i < Children.size(); i++)	{
		Children[i].SetColor(C);
	}
}

int Sprite::AddSprite(Point p, float s, bool iN)	{
	Children.push_back(Sprite(Point(Position.X + p.X, Position.Y + p.Y), s, iN));
	return Children.size() - 1;
}

int Sprite::AddLine(bool HasCollision, Point P1, Point P2, Color C1, Color C2)	{
	if (C1.isEmpty == 1)	{C1 = _dC;}
	if (C2.isEmpty == 1)	{C2 = C1;}
	_vList.push_back(_ElementObject());
	glGenBuffers(1, &_vList[_vC].vboID);
	_vList[_vC].Type = SpriteType::LINE;
	_vList[_vC].HasCollision = HasCollision;
	_vList[_vC].Point = std::vector<Point>(2);
	_vList[_vC].Point[0] = P1;
	_vList[_vC].Point[1] = P2;
	_vList[_vC].Color = std::vector<Color>(2);
	_vList[_vC].Color[0] = C1;
	_vList[_vC].Color[1] = C2;
	if (_collisionObjId == -1)	{
		_AdjustCollisionField(_vList[_vC].Point);
	}
	_DrawObject(_vC);
	_vC ++;
	return _vC - 1;
}

int Sprite::AddTriangle(bool HasCollision, Point P1, Point P2, Point P3, Color C1, Color C2, Color C3)	{
	if (C1.isEmpty == 1)	{C1 = _dC;}
	if (C2.isEmpty == 1)	{C2 = C1;}
	if (C3.isEmpty == 1)	{C3 = C1;}
	_vList.push_back(_ElementObject());
	glGenBuffers(1, &_vList[_vC].vboID);
	_vList[_vC].Type = SpriteType::TRIANGLE;
	_vList[_vC].HasCollision = HasCollision;
	_vList[_vC].Point = std::vector<Point>(3);
	_vList[_vC].Point[0] = P1;
	_vList[_vC].Point[1] = P2;
	_vList[_vC].Point[2] = P3;
	_vList[_vC].Color = std::vector<Color>(3);
	_vList[_vC].Color[0] = C1;
	_vList[_vC].Color[1] = C2;
	_vList[_vC].Color[2] = C3;
	if (_collisionObjId == -1)	{
		_AdjustCollisionField(_vList[_vC].Point);
	}
	_DrawObject(_vC);
	_vC ++;
	return _vC - 1;
}

int Sprite::AddRect(bool HasCollision, Point P, Size S, Color C1, Color C2)	{
	if (C1.isEmpty == 1)	{C1 = _dC;}
	if (C2.isEmpty == 1)	{C2 = C1;}
	_vList.push_back(_ElementObject());
	glGenBuffers(1, &_vList[_vC].vboID);
	_vList[_vC].Type = SpriteType::RECT;
	_vList[_vC].HasCollision = HasCollision;
	_vList[_vC].Point = std::vector<Point>(4);
	_vList[_vC].Point[0] = P;
	_vList[_vC].Point[1] = Point(P.X, P.Y + S.Height);
	_vList[_vC].Point[2] = Point (P.X + S.Width, P.Y + S.Height);
	_vList[_vC].Point[3] = Point(P.X + S.Width, P.Y);
	_vList[_vC].Color = std::vector<Color>(2);
	_vList[_vC].Color[0] = C1;
	_vList[_vC].Color[1] = C2;
	if (_collisionObjId == -1)	{
		_AdjustCollisionField(_vList[_vC].Point);
	}
	_DrawObject(_vC);
	_vC ++;
	return _vC - 1;
}

int Sprite::AddTexture(bool HasCollision, Point P, Size S, std::string TexturePath)	{
	_vList.push_back(_ElementObject());
	glGenBuffers(1, &_vList[_vC].vboID);
	_vList[_vC].Type = SpriteType::TEXTURE;
	_vList[_vC].HasCollision = HasCollision;	
	_vList[_vC].Texture = Resources.GetTexture(TexturePath);
	_vList[_vC].Point = std::vector<Point>(4);
	_vList[_vC].Point[0] = P;
	_vList[_vC].Point[1] = Point(P.X, P.Y + S.Height);
	_vList[_vC].Point[2] = Point (P.X + S.Width, P.Y + S.Height);
	_vList[_vC].Point[3] = Point(P.X + S.Width, P.Y);
	if (_collisionObjId == -1)	{
		_AdjustCollisionField(_vList[_vC].Point);
	}
	_DrawObject(_vC);
	_vC ++;
	return _vC - 1;
}

void Sprite::_DrawObject(int vId)	{
	std::vector<Vertex> vD(_vList[vId].Point.size());
	for (size_t i = 0; i < _vList[vId].Point.size(); i++)	{
		vD[i].Position = _vList[vId].Point[i];
		if (_iN == true)	{
			vD[i].Position.X = Position.X + (vD[i].Position.X * Scale);
			vD[i].Position.Y = Position.Y + (vD[i].Position.Y * Scale);
		}else	{
			vD[i].Position.X = (Position.X + (vD[i].Position.X * Scale)) / 500 - 1;
			vD[i].Position.Y = (Position.Y + (vD[i].Position.Y * Scale)) / (500) - 1;
		}
		if (_vList[vId].Type == SpriteType::TEXTURE)	{
			vD[i].Color = Color(255, 255, 255, 255);
		}else	{
			vD[i].Color = _vList[vId].Color[i];
		}
	}
	if (_vList[vId].Type == SpriteType::RECT)	{
		vD[0].Color = _vList[vId].Color[0];
		vD[3].Color = _vList[vId].Color[1];
	}else if (_vList[vId].Type == SpriteType::TEXTURE)	{
		vD[0].UV = UV(0.0f, 0.0f);
		vD[1].UV = UV(0.0f, 1.0f);
		vD[2].UV = UV(1.0f, 1.0f);
		vD[3].UV = UV(1.0f, 0.0f);
	}
	glBindBuffer(GL_ARRAY_BUFFER, _vList[vId].vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vD[0]) * vD.size(), &vD[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::_UpdateList()	{
	for (size_t i = 0; i < _vList.size(); i++)	{
		_DrawObject(i);
	}
}

void Sprite::Update()	{
	for (size_t i = 0; i < _vList.size(); i++)	{
		glBindBuffer(GL_ARRAY_BUFFER, _vList[i].vboID);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, Color));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, UV));
		if (_vList[i].Type == SpriteType::TEXTURE)	{
			glUniform1i(ColorProgram.getUniformLocation("isTexture"), GL_TRUE);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, _vList[i].Texture.id);
			glUniform1i(ColorProgram.getUniformLocation("curTexture"), 0);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
			glDrawArrays(GL_QUADS, 0, 4);
			glBindTexture(GL_TEXTURE_2D, 0);
		}else	{
			glUniform1i(ColorProgram.getUniformLocation("isTexture"), GL_FALSE);
		}
		if(_vList[i].Type == SpriteType::LINE)	{
			glLineWidth(1.0);
			glDrawArrays(GL_LINES, 0, 2);
		}else if (_vList[i].Type == SpriteType::TRIANGLE)	{
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}else if (_vList[i].Type == SpriteType::RECT)	{
			glDrawArrays(GL_QUADS, 0, 4);
		}
		glDisableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}	

void Sprite::UpdateChildren()	{
	for (size_t i = 0; i < Children.size(); i++)	{
		Children[i].Update();
	}
}







//COLLISION DETECTION SYSTEM
void Sprite::_AdjustCollisionField(std::vector<Point> Points)	{
	float curPos;
	for (size_t i = 0; i < Points.size(); i++)	{
		curPos = Position.X + (Points[i].X * Scale);
		if (CollisionField.BottomLeft.X > curPos)	{
			CollisionField.BottomLeft.X = curPos;
		}else if (CollisionField.TopRight.X < curPos)	{
			CollisionField.TopRight.X = curPos;
		}
		curPos = Position.Y + (Points[i].Y * Scale);
		if (CollisionField.BottomLeft.Y > curPos)	{
			CollisionField.BottomLeft.Y = curPos;
		}else if (CollisionField.TopRight.Y < curPos)	{
			CollisionField.TopRight.Y = curPos;
		}
	}
	CollisionField.Size.Width = CollisionField.TopRight.X - CollisionField.BottomLeft.X;
	CollisionField.Size.Height = CollisionField.TopRight.Y - CollisionField.BottomLeft.Y;
	std::cout << "(" << CollisionField.BottomLeft.X << "," << CollisionField.BottomLeft.Y << ")" << std::endl;
	std::cout << "(" << CollisionField.TopRight.X << "," << CollisionField.TopRight.Y << ")" << std::endl;
}



void Sprite::SetCollisionObject(int oId)	{
	_collisionObjId = oId;
	CollisionField.Type = _vList[oId].Type;
	_AdjustCollisionField(_vList[oId].Point);
}

CollisionData Sprite::PredictCollision(Sprite cS, Point tTP)	{
	CollisionData cD = CollisionData();
	Point tP = _scaleMoveToFrame(tTP);
	Point bS[4]; //Current Sprite Coord's, including the movement involved.
	bS[0] = Point(CollisionField.BottomLeft.X + tP.X, CollisionField.BottomLeft.Y + tP.Y);
	bS[1] = Point(CollisionField.BottomLeft.X + tP.X, CollisionField.TopRight.Y + tP.Y);
	bS[2] = Point(CollisionField.TopRight.X + tP.X, CollisionField.TopRight.Y + tP.Y);
	bS[3] = Point(CollisionField.TopRight.X + tP.X, CollisionField.BottomLeft.Y + tP.Y);



	for (int i = 0; i < 4; i++)	{
		if (bS[i].X >= cS.CollisionField.BottomLeft.X && bS[i].X <= cS.CollisionField.TopRight.X && //THIS JUST CHECKS IF ITS CLOSE (TREATING THE OBJECT LIKE A BOX)
			bS[i].Y >= cS.CollisionField.BottomLeft.Y && bS[i].Y <= cS.CollisionField.TopRight.Y)	{ //YAY BASE COLLISION, NOW CHECK WHAT KIND OF OBJECT WE'RE REALLY CHECKING
					cD.isCollided = true;
				//if (CollisionField.Type == CollisionField.ALPHAMASK)	{//THIS IS 
				//}
			
		}
	}


	return cD;
}












