#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <math.h>
#include <vector>
#include <list>
#include <D3Dcompiler.h>
#include <Windows.h>
#include <d3d11.h>
#include <map>
#include <functional>
#include <algorithm>

//btよりも下に書くとoperator-があいまいになるよ(^^)。
#include "DirectXTK\Inc\Audio.h"

#include "btBulletDynamicsCommon.h"
#include "BulletCollision\CollisionDispatch\btGhostObject.h"

//DirectXTKのインクルードファイル。
#include "DirectXTK/Inc/Model.h"
#include "DirectXTK/Inc/Effects.h"	
#include "DirectXTK/Inc/CommonStates.h"
#include "DirectXTK/Inc/SpriteFont.h"
#include "DirectXTK/Inc/DDSTextureLoader.h"

#include "physics/Physics.h"
#include "HID/Pad.h"

#include "math/Vector.h"
#include "math/Matrix.h"
#include "graphics/GraphicsEngine.h"

#include "graphics/SkinModel.h"
#include "graphics/Skeleton.h"

#include "graphics/animation/Animation.h"
#include "graphics/animation/AnimationClip.h"
#include "graphics/Camera.h"

//こっから自分やで。
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Noncopy.h"
#include "Sprite.h"
#include "SpriteRender.h"
#include "SkinModelRender.h"
#include "FontRender.h"
#include "sound/CSound.h"

const float FRAME_BUFFER_W = 1280.0f;				//フレームバッファの幅。
const float FRAME_BUFFER_H = 720.0f;				//フレームバッファの高さ。

const float SCREENWIDTH_W = 1280.0f;				//2D空間の幅。		//todo　途中から作ったのですべてに使えてるわけではない
const float SCREENHEIGHT_H = 720.0f;				//2D空間の高さ。

static const int MAX_BONE = 512;	//!<ボーンの最大数。

#include <xaudio2.h>
#include <x3daudio.h>
#include <xaudio2fx.h>
