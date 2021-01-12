#pragma once
#include <vector>

class GlobalFormat
{
	template<typename T>
	using vector = std::vector<T>;

public:
	struct Format5x5
	{
		bool shape[5][5];
	};

private:
	static vector<Format5x5> playerShapeLv1;
	static vector<Format5x5> playerShapeLv2;
	static vector<Format5x5> playerShapeLv3;
	static vector<Format5x5> playerShapeLv4;

	static int level;
	static int score;

public:
	static void Initialize();
	static void Clear();

	/// <summary>
	/// ���x���ɉ������v���C���[�̌`��������_���ŕԂ�
	/// </summary>
	/// <param name="level">��Փx</param>
	/// <returns>�v���C���[�̌`��</returns>
	static Format5x5 GetPlayerShape(int level);

	/// <summary>
	/// ���x���ɉ������ǂ̌`��������_���ŕԂ�
	/// </summary>
	/// <param name="level">��Փx</param>
	/// <returns></returns>
	static Format5x5 GetWallShape(int level, Format5x5 playerFormat);

	/// <summary>
	/// ���x�����Z�b�g����
	/// </summary>
	static void SetLevel(int level) { GlobalFormat::level = level; }

	/// <summary>
	/// �X�R�A���Z�b�g����
	/// </summary>
	static void SetScore(int score) { GlobalFormat::score = score; }

	/// <summary>
	/// ���x�����擾����
	/// </summary>
	/// <returns>���x��</returns>
	static int GetLevel() { return GlobalFormat::level; }

	/// <summary>
	/// �X�R�A���擾����
	/// </summary>
	/// <returns>�X�R�A</returns>
	static int GetScore() { return GlobalFormat::score; }
};
