
//---------------------------------------------------------------------------------------------------------------------------------------------
//                                              �`�ʂ���}�b�v���Ǘ�����N���X(�e�X�g�N���X)
// 
// �}�b�v�`�b�v����ׂ�int�z������Ƀ}�b�v�̍��W���Ǘ����A�`�悷��
// �`��ł���X�N���[���̃T�C�Y�Ɠ����傫����������int�z���primarymap��secondarymap�����݂ɕ`�悷�邱�ƂŃX�N���[������
//---------------------------------------------------------------------------------------------------------------------------------------------

#include "TestMapManager.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "GameTexture.h"



using namespace MapConfig;      //map�T�C�Y��`�b�v�T�C�Y�Ȃǂ���`����Ă���萔�̏W�܂�

//.cpp���Ŏg���萔
namespace {
    constexpr int ZERO_INDEX_OFFSET = 1;           //���[�v�̍ۂɃC���f�b�N�X����납�琔����ꍇ�̃I�t�Z�b�g�l
    constexpr int DRAWMAP_SIZE = MAP_H * MAP_W;      //1�t���[���ŃJ�E���g�����ꍇ�̃}�b�v�̗�
    constexpr int DRAWMAP_HIGH = MAP_H * CHIP_SIZE;      //1�t���[���ŃJ�E���g�����ꍇ�̃}�b�v�̗�
    constexpr int DRAWMAP_RANGE = DRAWMAP_HIGH * 2;      //��̃}�b�v���`�悷�鋗��(�t���[���C������t���[���A�E�g�܂�)
    constexpr int PARTITION_MAX = 4;                     //�}�b�v�̕�����
    constexpr int INIT_Y_OFFSET = -DRAWMAP_HIGH;      //�}�b�v���`��͈͂ɓ���O��y���W�̕␳�l(�`��͈�Ԍ��̃C���f�b�N�X����n�܂�̂ō�����W��DRAWMAP_HIGH�������K�v������)
}

TestMapManager::TestMapManager(std::shared_ptr<ResourceManager> rm) : currentnumber(0), currentpartition(0),
mapchip(0), mapdata({}), backmap({}),
primarymap({ false, {}, 0, 0 }),
secondarymap({ false, {},0,0 })
{
    mapchip = rm->GetTexture(TextureType::Map);
    SetDrawMapData(rm->ConvertDrawMapCsv_Vector());
}

//=======================================================================================
//                      ������
// 
// �Q�[���n�߂�Ƃ��̏����ݒ������
//=======================================================================================
int TestMapManager::Init()
{
    currentpartition = 0;                       //�X�e�[�W�̍ŏ�����ɂȂ�悤��currentpartition��0�ɂ���
    MapDataUpdate(primarymap, DRAWMAP_HIGH);    //�X�^�[�g����map�S�Ă��`�悳�ꂢ���Ԃɂ��邽�߁Ay���W�𒲐�����
    MapDataUpdate(secondarymap, 0);             //�X�^�[�g���ł����i�ʂ��ʂ̏ォ��`�ʂ��J�n����
    
    return 0;
}

//=======================================================================================
//                      �X�V
// 
// ��Ƀ}�b�v��y���W���X�V����B
// y���W����苗���ɂȂ�����Aint�z����X�V���čĂ�y���W0����`�ʂ��ĊJ����
//=======================================================================================
int TestMapManager::Update()
{
    primarymap.y++;        //�v���C�}���}�b�v��y���W���X�V����
    secondarymap.y++;      //�Z�J���_���}�b�v��y���W���X�V����

    if (primarymap.y >= DRAWMAP_RANGE)      MapDataUpdate(primarymap, 0);       //�v���C�}���}�b�vy���W����苗���i�񂾂�}�b�v���X�V����
    if (secondarymap.y >= DRAWMAP_RANGE)    MapDataUpdate(secondarymap,0);      //�Z�J���_���}�b�vy���W����苗���i�񂾂�}�b�v���X�V����
    
    return 0;
}

//=======================================================================================
//                   int�z����X�V����(private�֐�)
// 
// �}�b�v�`�b�v�̔z�u�����Ă���int�z�񂩂�}�b�v�T�C�Y�ɕ��������z����󂯎��B
// ������2 �̒l��y���W�̏����l��ݒ肷��
//=======================================================================================
void TestMapManager::MapDataUpdate(MapStatus& map,int startprogress = 0)
{
    map.y = startprogress;      //y���W�̏����l��ݒ肷��(�w�肪�Ȃ����0)

    int indexoffset = DRAWMAP_SIZE * currentpartition - ZERO_INDEX_OFFSET;       //�X�e�[�W�̐i�s�x�ɉ����Ď擾����C���f�b�N�X�ɕ␳��������
    for (int r = 0; r < MAP_H; r++) {
        for (int r2 = 0; r2 < MAP_W; r2++) {
            int counter = r2 + (r * MAP_W);        //���[�v�����1�J�E���g����l
            map.data[counter] = currentpartition == 0 ? 0 : mapdata[indexoffset - counter];     //�i�s�x��0�̏ꍇ�}�b�v�`�b�v�͑S��0�œ��ꂷ��(�X�^�[�g�G���A)
                                                                                                //����ȊO�Ȃ�int�z�񂩂�}�b�v�`�b�v�̔z�u���󂯂Ƃ�
        }
    }

    currentpartition++;
    if (currentpartition > PARTITION_MAX) currentpartition = 0;
}

int TestMapManager::Draw()
{
    for (int r = 0; r < MAP_H; r++) {
        for (int r2 = 0; r2 < MAP_W; r2++) {
            int counter = r2 + (r * MAP_W);
            int x = r2 * CHIP_SIZE;
            int y = INIT_Y_OFFSET + r * CHIP_SIZE;
            render_->DrawFromTopLeftPos(mapchip, primarymap.data[counter], x, primarymap.y + y);
            render_->DrawFromTopLeftPos(mapchip, secondarymap.data[counter], x, secondarymap.y + y);
        }
    }

    return 0;
}

//=============================================================================================
//                              �}�b�v�`�b�v�摜�̃��[�h
//=============================================================================================

inline bool TestMapManager::LoadMapChipTexture(std::shared_ptr<GameTexture> tex) {
    // �e�N�X�`�����L�����ǂ������m�F����
    if (!tex) {
        std::cerr << "Failed to load map chip texture: tex is null." << std::endl;
        return false;  // ���s������
    }

    // ����ɓǂݍ��܂ꂽ�ꍇ
    mapchip = tex;
    return true;        // ����������
}
