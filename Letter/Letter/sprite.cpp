#include "sprite.h";


//COMMON FUNCTIONS --TODO, MOVE TO COMMON FUNC.CPP
double Common_Round(double num)	{
	return (num > 0.0) ? floor(num + 0.5) : ceil(num - 0.5);
}

//OTHER SHIT

float LineLength(Point P1, Point P2)	{
	return sqrt((P2.X - P1.X) * (P2.X - P1.X) + (P2.Y - P1.Y) * (P2.Y - P1.Y));
}

bool LineIntersection(Point l1a, Point l1b, Point l2a, Point l2b, Point *iP)	{
	//Get the line-point offsets.
	float d1x, d1y, d2x, d2y;
	d1x = l1b.X - l1a.X;	d1y = l1b.Y - l1a.Y;
	d2x = l2b.X - l2a.X;	d2y = l2b.Y - l2a.Y;

	//I don't know how this works yet, unfortunate copy paste from online (Had to get this working ASAP)
	float s, t;
	s = (-d1y * (l1a.X - l2a.X) + d1x * (l1a.Y - l2a.Y)) / (-d2x * d1y + d1x * d2y);
	t = (d2x * (l1a.Y - l2a.Y) - d2y * (l1a.X - l2a.X)) / (-d2x * d1y + d1x * d2y);
	if (s >= 0 && s <= 1 && t >= 0 && t <= 1)	{ //Collision detected, return intersection point
		if (iP != NULL)	{
			*iP = Point(l1a.X + (t * d1x), l1a.Y + (t * d1y)); //Set passed in variable to the collision intersection point
		}
		return true;
	}
	return false;
}

bool isPointOnLine (Point p, Point lA, Point lB) {
    Point vA = Point (lA.X - lB.X, lA.Y - lB.Y);
    Point vB = Point (p.X - lB.X, p.Y - lB.Y);
    float area = vA.X * vB.Y - vA.Y * vB.X;
    if (abs (area) < 0.01f)
        return true;
    return false;
}

float LineAngle (Point lA, Point lB)	{
	return atan2(lB.Y - lA.Y, lB.X - lA.X);
}
float RadianToDegree (float r)	{
	return r * 180 / 3.141592f;
}


bool PredictCollision(Sprite sA, Sprite sB, Point t, Point *rT, float *angle)	{
	if (t.X == 0 && t.Y == 0)	{
		return false;
	}

	Point rP, tempP;
	float sL = INFINITE, tempL, tempA;
	Point l1a, l1b, l1t, l2a, l2b, l2t;
	for (size_t aI = 0; aI < sA.Element.size(); aI++)	{if (sA.Element[aI].HasCollision == true)	{
		for (size_t aEI = 0; aEI < sA.Element[aI].Point.size(); aEI++)	{
			l1a = Point(sA.Element[aI].Point[aEI].X + sA.Position.X, sA.Element[aI].Point[aEI].Y + sA.Position.Y);
			if (aEI == sA.Element[aI].Point.size())	{
				l1b = Point(sA.Element[aI].Point[0].X + sA.Position.X, sA.Element[aI].Point[0].Y + sA.Position.Y);
			}else	{
				l1b = Point(sA.Element[aI].Point[aEI + 1].X + sA.Position.X, sA.Element[aI].Point[aEI + 1].Y + sA.Position.Y);
			}
			l1t = Point (l1a.X + t.X, l1a.Y + t.Y);

			for (size_t bI = 0; bI < sB.Element.size(); bI++)	{if (sB.Element[bI].HasCollision == true)	{
				for (size_t bEI = 0; bEI < sB.Element[bI].Point.size(); bEI++)	{
					l2a = Point (sB.Element[bI].Point[bEI].X + sB.Position.X, sB.Element[bI].Point[bEI].Y + sB.Position.Y);
					if (bEI == sB.Element[bI].Point.size())	{
						l2b = Point (sB.Element[bI].Point[0].X + sB.Position.X, sB.Element[bI].Point[0].Y + sB.Position.Y);
					}else	{
						l2b = Point (sB.Element[bI].Point[bEI + 1].X + sB.Position.X, sB.Element[bI].Point[bEI + 1].Y + sB.Position.Y);
					}
					l2t = Point (l2a.X - t.X, l2a.Y - t.Y);


					//Check if point in already on the line, or line is already on the point.
					l1t = Point (l1a.X + t.X, l1a.Y + t.Y);
					if (isPointOnLine(l2a, l2b, l1a) == true || isPointOnLine(l1a, l1b, l2a) == true)	{
						//If angle is < 30 then forget about Y;
						float test = RadianToDegree(LineAngle(l2a, l2b));
						if (test >= 180.0f)		test -= 180.0f;
						if (test <= 30)	{
							l1t.Y = l1a.Y;
						}
						std::cout << l1t.Y << std::endl;
					}
					if (LineIntersection(l1a, l1t, l2a, l2b, &tempP) == true)	{
						
						
						tempP = Point (tempP.X - l1a.X, tempP.Y - l1a.Y);
						tempL = LineLength(Point (0, 0), tempP);
						if (tempL < sL)	{
							sL = tempL;
							rP = tempP;
							tempA = LineAngle(l2a, l2b);// * 180 / 3.14159f;
						}
					}













				}
			}}
		}
	}}


	if (sL != INFINITE)	{
		*rT = rP;
		*angle = tempA;
		return true;
	}
	return false;
}



bool HandleCollision(Sprite CompareFrom, Sprite CompareTo)	{
	Point v = CompareFrom.Velocity;
	if (v.X == 0 && v.Y == 0)	{
		return false; //No transformation, just exit without wasting thousands of itterations
	}






}







//RENDER SPRITE INITIALIZER
Sprite::Sprite(Point Position, float cScale, bool fixed, bool isNormalized) : _vC(0), Position(Position), Weight(1.0f), Scale(cScale), Fixed(fixed), _iN(isNormalized), _collisionObjId(-1), CollisionField(_CollisionFieldObject())	{
	CollisionField.Type = SpriteType::RECT;
	CollisionField.BottomLeft = Position;
	CollisionField.TopRight = Position;
}
Sprite::~Sprite()	{

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
	Position.X += OffsetPoint.X;
	CollisionField.BottomLeft.X += OffsetPoint.X;
	CollisionField.TopRight.X += OffsetPoint.X;
	Position.Y += OffsetPoint.Y;
	CollisionField.BottomLeft.Y += OffsetPoint.Y;
	CollisionField.TopRight.Y += OffsetPoint.Y;
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

Point ScaleVelocityToFrameRate(Point Vel)	{
	return Point(Vel.X * (float)FrameTimeElapsed * PixelsPerSecond, Vel.Y * (float)FrameTimeElapsed * PixelsPerSecond);
}Point UnScaleVelocityToFrameRate(Point Vel)	{
	return Point(Vel.X / (float)FrameTimeElapsed / PixelsPerSecond, Vel.Y / (float)FrameTimeElapsed / PixelsPerSecond);
}

void Sprite::SetVelocity(Point v)	{
	Velocity = ScaleVelocityToFrameRate(v);
	for (size_t i = 0; i < Element.size(); i++)	{
		for (size_t j = 0; j < Element[i].Point.size(); j++)	{
			Element[i].Velocity[i] = Velocity;
		}
	}
}void Sprite::SetVelocityX(float xV)	{
	Velocity.X = ScaleVelocityToFrameRate(Point (xV, 0)).X;
	for (size_t i = 0; i < Element.size(); i++)	{
		for (size_t j = 0; j < Element[i].Point.size(); j++)	{
			Element[i].Velocity[i].X = Velocity.X;
		}
	}
}void Sprite::SetVelocityY(float yV)	{
	Velocity.Y = ScaleVelocityToFrameRate(Point (0, yV)).Y;
	for (size_t i = 0; i < Element.size(); i++)	{
		for (size_t j = 0; j < Element[i].Point.size(); j++)	{
			Element[i].Velocity[i].Y = Velocity.Y;
		}
	}
}

void Sprite::ApplyGravity(float g)	{
	g = ScaleVelocityToFrameRate(Point (0, g * Weight)).Y;
	Velocity = Point (Velocity.X, Velocity.Y - g);
	for (size_t i = 0; i < Element.size(); i++)	{
		for (size_t j = 0; j < Element[i].Point.size(); j++)	{
			Element[i].Velocity[i] = Point (Element[i].Velocity[i].X, Element[i].Velocity[i].Y - g);
		}
	}
}

int Sprite::AddSprite(Point p, float s, bool iN)	{
	Children.push_back(Sprite(Point(Position.X + p.X, Position.Y + p.Y), s, iN));
	return Children.size() - 1;
}

int Sprite::AddLine(bool HasCollision, Point P1, Point P2, Color C1, Color C2)	{
	if (C1.isEmpty == 1)	{C1 = _dC;}
	if (C2.isEmpty == 1)	{C2 = C1;}
	Element.push_back(ElementObject());
	glGenBuffers(1, &Element[_vC].vboID);
	Element[_vC].Type = SpriteType::LINE;
	Element[_vC].HasCollision = HasCollision;
	Element[_vC].Point = std::vector<Point>(2);
	Element[_vC].Point[0] = P1;
	Element[_vC].Point[1] = P2;
	Element[_vC].Color = std::vector<Color>(2);
	Element[_vC].Color[0] = C1;
	Element[_vC].Color[1] = C2;
	Element[_vC].Velocity = std::vector<Point>(2);
	if (_collisionObjId == -1)	{
		_AdjustCollisionField(Element[_vC].Point);
	}
	_DrawObject(_vC);
	_vC ++;
	return _vC - 1;
}

int Sprite::AddTriangle(bool HasCollision, Point P1, Point P2, Point P3, Color C1, Color C2, Color C3)	{
	if (C1.isEmpty == 1)	{C1 = _dC;}
	if (C2.isEmpty == 1)	{C2 = C1;}
	if (C3.isEmpty == 1)	{C3 = C1;}
	Element.push_back(ElementObject());
	glGenBuffers(1, &Element[_vC].vboID);
	Element[_vC].Type = SpriteType::TRIANGLE;
	Element[_vC].HasCollision = HasCollision;
	Element[_vC].Point = std::vector<Point>(3);
	Element[_vC].Point[0] = P1;
	Element[_vC].Point[1] = P2;
	Element[_vC].Point[2] = P3;
	Element[_vC].Color = std::vector<Color>(3);
	Element[_vC].Color[0] = C1;
	Element[_vC].Color[1] = C2;
	Element[_vC].Color[2] = C3;
	Element[_vC].Velocity = std::vector<Point>(3);
	if (_collisionObjId == -1)	{
		_AdjustCollisionField(Element[_vC].Point);
	}
	_DrawObject(_vC);
	_vC ++;
	return _vC - 1;
}

int Sprite::AddRect(bool HasCollision, Point P, Size S, Color C1, Color C2)	{
	if (C1.isEmpty == 1)	{C1 = _dC;}
	if (C2.isEmpty == 1)	{C2 = C1;}
	Element.push_back(ElementObject());
	glGenBuffers(1, &Element[_vC].vboID);
	Element[_vC].Type = SpriteType::RECT;
	Element[_vC].HasCollision = HasCollision;
	Element[_vC].Point = std::vector<Point>(4);
	Element[_vC].Point[0] = P;
	Element[_vC].Point[1] = Point(P.X, P.Y + S.Height);
	Element[_vC].Point[2] = Point (P.X + S.Width, P.Y + S.Height);
	Element[_vC].Point[3] = Point(P.X + S.Width, P.Y);
	Element[_vC].Color = std::vector<Color>(2);
	Element[_vC].Color[0] = C1;
	Element[_vC].Color[1] = C2;
	Element[_vC].Velocity = std::vector<Point>(4);
	if (_collisionObjId == -1)	{
		_AdjustCollisionField(Element[_vC].Point);
	}
	_DrawObject(_vC);
	_vC ++;
	return _vC - 1;
}

int Sprite::AddTexture(bool HasCollision, Point P, Size S, std::string TexturePath)	{
	Element.push_back(ElementObject());
	glGenBuffers(1, &Element[_vC].vboID);
	Element[_vC].Type = SpriteType::TEXTURE;
	Element[_vC].HasCollision = HasCollision;	
	Element[_vC].Texture = Resources.GetTexture(TexturePath);
	Element[_vC].Point = std::vector<Point>(4);
	Element[_vC].Point[0] = P;
	Element[_vC].Point[1] = Point(P.X, P.Y + S.Height);
	Element[_vC].Point[2] = Point (P.X + S.Width, P.Y + S.Height);
	Element[_vC].Point[3] = Point(P.X + S.Width, P.Y);
	Element[_vC].Velocity = std::vector<Point>(4);
	if (_collisionObjId == -1)	{
		_AdjustCollisionField(Element[_vC].Point);
	}
	_DrawObject(_vC);
	_vC ++;
	return _vC - 1;
}

void Sprite::_DrawObject(int vId)	{
	std::vector<Vertex> vD(Element[vId].Point.size());
	for (size_t i = 0; i < Element[vId].Point.size(); i++)	{
		vD[i].Position = Element[vId].Point[i];
		if (_iN == true)	{
			vD[i].Position.X = Position.X + (vD[i].Position.X * Scale);
			vD[i].Position.Y = Position.Y + (vD[i].Position.Y * Scale);
		}else	{
			vD[i].Position.X = (Position.X + (vD[i].Position.X * Scale)) / 500 - 1;
			vD[i].Position.Y = (Position.Y + (vD[i].Position.Y * Scale)) / (500) - 1;
		}
		if (Element[vId].Type == SpriteType::TEXTURE)	{
			vD[i].Color = Color(255, 255, 255, 255);
		}else if(Element[vId].Type != SpriteType::RECT)	{
			vD[i].Color = Element[vId].Color[i];
		}
	}
	if (Element[vId].Type == SpriteType::RECT)	{
		vD[0].Color = Element[vId].Color[0];
		vD[1].Color = Element[vId].Color[0];
		vD[2].Color = Element[vId].Color[1];
		vD[3].Color = Element[vId].Color[1];
	}else if (Element[vId].Type == SpriteType::TEXTURE)	{
		vD[0].UV = UV(0.0f, 0.0f);
		vD[1].UV = UV(0.0f, 1.0f);
		vD[2].UV = UV(1.0f, 1.0f);
		vD[3].UV = UV(1.0f, 0.0f);
	}
	glBindBuffer(GL_ARRAY_BUFFER, Element[vId].vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vD[0]) * vD.size(), &vD[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::_UpdateList()	{
	for (size_t i = 0; i < Element.size(); i++)	{
		_DrawObject(i);
	}
}

void Sprite::Update()	{
	for (size_t i = 0; i < Element.size(); i++)	{
		glBindBuffer(GL_ARRAY_BUFFER, Element[i].vboID);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, Color));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, UV));
		if (Element[i].Type == SpriteType::TEXTURE)	{
			glUniform1i(ColorProgram.getUniformLocation("isTexture"), GL_TRUE);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, Element[i].Texture.id);
			glUniform1i(ColorProgram.getUniformLocation("curTexture"), 0);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
			glDrawArrays(GL_QUADS, 0, 4);
			glBindTexture(GL_TEXTURE_2D, 0);
		}else	{
			glUniform1i(ColorProgram.getUniformLocation("isTexture"), GL_FALSE);
		}
		if(Element[i].Type == SpriteType::LINE)	{
			glLineWidth(1.0);
			glDrawArrays(GL_LINES, 0, 2);
		}else if (Element[i].Type == SpriteType::TRIANGLE)	{
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}else if (Element[i].Type == SpriteType::RECT)	{
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
}



void Sprite::SetCollisionObject(int oId)	{
	_collisionObjId = oId;
	CollisionField.Type = Element[oId].Type;
	_AdjustCollisionField(Element[oId].Point);
}






