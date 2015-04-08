
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

bool PredictCollision(Sprite sA, Sprite sB, Point t, Point *rT)	{
	if (t.X == 0 && t.Y == 0)	{
		return false;
	}
	float oX = 0, oY = 0;
	if (t.X > 0)	{oX = 0.0001f;}
	if (t.X < 0)	{oX = -0.0001f;}
	if (t.Y > 0)	{oY = 0.0001f;}
	if (t.Y < 0)	{oY = -0.0001f;}
	Point returnPoint;
	std::vector<Point> interseptPoints;
	Point l1a, l1b, t1a, t1b, l2a, l2b, t2a, t2b;
	for (size_t aI = 0; aI < sA.Element.size(); aI++)	{ //Cycle through all sprite elements in sprite A
		if (sA.Element[aI].HasCollision == true)	{ //Check if element has collision on...
			for (size_t bI = 0; bI < sB.Element.size(); bI++)	{ //Cycle through all sprite elements in sprite B
				if (sB.Element[bI].HasCollision == true)	{ //Check if element has collision on...
					for (size_t aEI = 0; aEI < sA.Element[aI].Point.size(); aEI++)	{ //Cycle through all points in sprite A element [aI]
						
						
						//Check if x or y is already colliding with sprite B. If so, only deal with the other axis transition. (Setting t.X or t.Y to 0)

						
						//l1 makes up a line in object 1
						l1a = Point(sA.Element[aI].Point[aEI].X + sA.Position.X + oX, sA.Element[aI].Point[aEI].Y + sA.Position.Y + oY);
						if (aEI == sA.Element[aI].Point.size())	{
							l1b = Point(sA.Element[aI].Point[0].X + sA.Position.X + oX, sA.Element[aI].Point[0].Y + sA.Position.Y + oY);
						}else	{
							l1b = Point(sA.Element[aI].Point[aEI + 1].X + sA.Position.X + oX, sA.Element[aI].Point[aEI + 1].Y + sA.Position.Y + oY);
						}
						//t1 = Makes up a line from a point in object 1 and the transition of the point.
						t1a = Point(sA.Element[aI].Point[aEI].X + sA.Position.X + oX, sA.Element[aI].Point[aEI].Y + sA.Position.Y + oY);
						t1b = Point (t1a.X + t.X, t1a.Y + t.Y);
						for (size_t bEI = 0; bEI < sB.Element[bI].Point.size(); bEI++)	{ //Cycle through all points in sprite B element [bI]
							l2a = Point (sB.Element[bI].Point[bEI].X + sB.Position.X, sB.Element[bI].Point[bEI].Y + sB.Position.Y);
							if (bEI == sB.Element[bI].Point.size())	{
								l2b = Point (sB.Element[bI].Point[0].X + sB.Position.X, sB.Element[bI].Point[0].Y + sB.Position.Y);
							}else	{
								l2b = Point (sB.Element[bI].Point[bEI + 1].X + sB.Position.X, sB.Element[bI].Point[bEI + 1].Y + sB.Position.Y);
							}
							t2a = Point(sB.Element[bI].Point[bEI].X + sB.Position.X, sB.Element[bI].Point[bEI].Y + sB.Position.Y);
							t2b = Point (t2a.X - t.X, t2a.Y - t.Y);
							if (LineIntersection(t1a, t1b, l2a, l2b, &returnPoint) == true)	{
								interseptPoints.push_back(Point (returnPoint.X - t1a.X - oX, returnPoint.Y - t1a.Y - oY));
							}
							if (LineIntersection(l1a, l1b, t2a, t2b, &returnPoint) == true)	{
								interseptPoints.push_back(Point (-(returnPoint.X - t2a.X + oX), -(returnPoint.Y - t2a.Y + oY)));
							}
						}
					}
				}
			}
		}
	}

	float ShortestLength = INFINITE, tempLength;
	int chosenLineId;
	if (interseptPoints.size() > 0)	{
		for (size_t i = 0; i < interseptPoints.size(); i++)	{
			tempLength = LineLength(Point (0, 0), interseptPoints[i]);
			if (tempLength < ShortestLength)	{
				ShortestLength = tempLength;
				chosenLineId = i;
			}
		}
		*rT = interseptPoints[chosenLineId];
		return true;
	}	

	return false;
}









//RENDER SPRITE INITIALIZER
Sprite::Sprite(Point Position, float cScale, bool isNormalized) : _vC(0), Position(Position), Scale(cScale), _iN(isNormalized), _collisionObjId(-1), CollisionField(_CollisionFieldObject())	{
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






