#include "stdafx.h"
#include "Result.h"
namespace {
	int score = 0;							//�擾�����X�R�A���i�[����B
	int getStar = 0;						//�l���������̐��B

	float m_sheet_w = 360.f;				//�V�[�g�̉摜�̕��B
	float m_sheet_h = 540.f;				//�V�[�g�̉摜�̍����B
	float m_star_w = 80.f;					//���̉摜�̕��B
	float m_star_h = 80.f;					//���̉摜�̍����B
}

//todo �}�W�b�N�i���o�[�͂��ׂĉ��B

Result::Result()
{
}


Result::~Result()
{
	if (m_spriteRenderSheet != nullptr) {				//�V�[�g����������Ă���Ƃ��B
		DeleteGO(m_spriteRenderSheet);					//�V�[�g�������B
	}
	for (int i = 0; i < m_starNum; i++) {				//���̔z�񕪃��[�v����B
		if (m_spriteRenderStar[i] != nullptr) {			//������������Ă�����B
			DeleteGO(m_spriteRenderStar[i]);			//���������B
			m_spriteRenderStar[i] = nullptr;			//�C���X�^���X��j���B
		}
	}
}


bool Result::Start()
{
	m_score = FindGO<Score>("score");				//�X�R�A�̃C���X�^���X���擾�B

	m_spriteRenderSheet = NewGO<SpriteRender>(0, "sprite");										//�X�v���C�g�N���X�𐶐��B
	m_spriteRenderSheet->Init(L"Assets/sprite/result_sheet.dds", m_sheet_w, m_sheet_h);			//�V�[�g�̏������B
	m_spriteRenderSheet->SetPosition(m_positionSheet);											//���W���������B
	m_spriteRenderSheet->SetScale(m_scaleSheet);												//�X�P�[�����������B

	m_positionStar[0] = m_positionSheet;			//��ڂ̐��̍��W�ɃV�[�g�̍��W�����B
	m_positionStar[0].x -= 80.f;					//���Ɉړ�����B
	m_positionStar[0].y -= 90.f;					//���Ɉړ�����B

	for (int i = 0; i < m_starNum; i++) {			//�������鐯�̐������[�v����B
		m_spriteRenderStar[i] = NewGO<SpriteRender>(1, "sprite");								//�X�v���C�g�N���X�𐶐��B
		m_spriteRenderStar[i]->Init(L"Assets/sprite/black_star.dds", m_star_w, m_star_h);		//���̏�����(�͂��߂͍�����)�B
		m_spriteRenderStar[i]->SetPosition(m_positionStar[i]);									//���W���������B
		m_spriteRenderStar[i]->SetScale(m_scaleStar[i]);										//�X�P�[�����������B

		if (i <= m_starNum - 1) {					//���̔z�񂪑��݂�����B
			m_positionStar[i + 1] = m_positionStar[i];											//���̐��̍��W�ɑO�̐��̍��W�����B
			m_positionStar[i + 1].x += 80.f;													//�E�Ɉړ�����B
		}
	}

	score = m_score->GetScore();				//�X�R�A���擾�B

	return true;
}

void Result::ChangeStar()
{

	if (score < m_score->GetStarOne()) {			//�X�R�A�����P�̃{�[�_�[�������Ȃ��Ƃ��B
		getStar = 0;								//���̐����O�ɁB
	}

	if (score >= m_score->GetStarOne() && score < m_score->GetStarTwo()) {		//���P�̂Ƃ��B
		getStar = 1;								//���̐����P�ɁB
	}

	if (score >= m_score->GetStarTwo() && score < m_score->GetStarThree()) {	//���Q�̂Ƃ��B
		getStar = 2;								//���̐����Q�ɁB
	}

	if (score >= m_score->GetStarThree()) {			//���R�̂Ƃ��B
		getStar = 3;								//���̐����R�ɁB
	}

	for (int i = 0; i < getStar; i++) {				//�l���������̐������[�v����B
		if (m_changeStarFlag[i] == false) {			//���摜��ύX���Ă��Ȃ������Ƃ��B
			m_spriteRenderStar[i]->Init(L"Assets/sprite/star.dds", m_star_w, m_star_h);			//���̃��f���ύX�B
			m_changeStarFlag[i] = true;				//���̉摜��ύX�����̂Ńt���O��Ԃ��B
		}
	}

	//todo ���ύX�̂Ƃ��ɂ͂��ߊg�債�Ă����Ԃŕ`�悵�Ă����A�k�����Č��̃T�C�Y�ɖ߂��A�j���[�V��������������B
}

void Result::Update()
{

}

//���̐��܂ł̃X�R�A�B
int Result::NexStarNum()
{
	if (score < m_score->GetStarOne()) {			//�X�R�A�����P�̃{�[�_�[�������Ȃ��Ƃ��B
		return m_score->GetStarOne() - score;		//���P�̃{�[�_�[����X�R�A�����Z�������̂�Ԃ��B
	}

	if (score < m_score->GetStarOne()) {			//�X�R�A�����P�̃{�[�_�[�������Ȃ��Ƃ��B
		return m_score->GetStarTwo() - score;									//���Q�̃{�[�_�[����X�R�A�����Z�������̂�Ԃ��B
	}

	if (score >= m_score->GetStarTwo() && score < m_score->GetStarThree()) {	//���Q�̂Ƃ��B
		return m_score->GetStarThree() - score;									//���R�̃{�[�_�[����X�R�A�����Z�������̂�Ԃ��B
	}

	if (score >= m_score->GetStarThree()) {			//���R�̂Ƃ��B
		return 0;									//0��Ԃ��B
	}

}

void Result::AfterFontRender()
{
	m_timer += gametime().GetFrameDeltaTime();			//�^�C�}�[�����Z�B

	//�X�e�[�W�B
	m_font.Begin();			//�`��J�n�B
	wchar_t text[64];														//�e�L�X�g�Ɏg���z��B
	swprintf_s(text, L"1");													//�e�L�X�g��ݒ�B
	m_positionFont.x = m_positionSheet.x + 50.f;							//X���W���w��B						
	m_positionFont.y = m_positionSheet.y + 148.f;							//Y���W���w��B
	m_font.Draw(text, m_positionFont, m_colorFont, 0.0f, m_scaleFont);		//�X�V�����B
	m_font.End();			//�`��I���B

	if (m_timer >= 0.5f) {
		//�`�b�v���Z�O�̃X�R�A�B
		m_font.Begin();			//�`��J�n�B
		wchar_t text2[64];														//�e�L�X�g�Ɏg���z��B
		swprintf_s(text2, L"%d", m_score->GetProfit());						//�e�L�X�g���w��B
		m_positionFont.y -= 50.f;												//Y���W���w��B
		m_font.Draw(text2, m_positionFont, m_colorFont, 0.0f, m_scaleFont);		//�X�V�����B
		m_font.End();			//�`��I���B
	}

	if (m_timer >= 1.f) {
		//�`�b�v�B
		m_font.Begin();			//�`��J�n�B
		wchar_t text3[64];														//�e�L�X�g�Ɏg���z��B
		swprintf_s(text3, L"%d", m_score->GetChip());						//�e�L�X�g���w��B
		m_positionFont.y -= 25.f;												//Y���W���w��B
		m_font.Draw(text3, m_positionFont, m_colorFont, 0.0f, m_scaleFont);		//�X�V�����B
		m_font.End();			//�`��I���B
	}

	if (m_timer >= 1.5f) {
		//�y�i���e�B�B
		m_font.Begin();			//�`��J�n�B
		wchar_t text4[64];														//�e�L�X�g�Ɏg���z��B
		swprintf_s(text4, L"%d", m_score->GetPenalty());						//�e�L�X�g���w��B
		m_positionFont.y -= 25.f;												//Y���W���w��B
		m_font.Draw(text4, m_positionFont, m_colorFont, 0.0f, m_scaleFont);		//�X�V�����B
		m_font.End();			//�`��I���B
	}

	if (m_timer >= 2.f) {
		//�݌v�X�R�A
		m_font.Begin();			//�`��J�n�B
		wchar_t text5[64];														//�e�L�X�g�Ɏg���z��B
		swprintf_s(text5, L"%d", m_score->GetScore());							//�e�L�X�g���w��B
		m_positionFont.x -= 70.f;												//X���W���w��B
		m_positionFont.y -= 32.f;												//Y���W���w��B
		float scaleScore = 1.2f;												//�t�H���g�̃X�P�[�����w��B
		m_font.Draw(text5, m_positionFont, m_colorFont, 0.0f, scaleScore);		//�X�V�����B
		m_font.End();			//�`��I���B
	}
	if (m_timer >= 2.5f) {
		ChangeStar();
	}

	if (m_timer >= 3.f) {
		//���̐��܂ł̃X�R�A�B
		m_font.Begin();			//�`��J�n�B
		wchar_t text6[64];														//�e�L�X�g�Ɏg���z��B
		swprintf_s(text6, L"%d", NexStarNum());						//�e�L�X�g���w��B
		m_positionFont.y -= 150.f;												//Y���W���w��B
		m_font.Draw(text6, m_positionFont, m_colorFont, 0.0f, m_scaleFont);		//�X�V�����B
		m_font.End();			//�`��I���B
	}
}