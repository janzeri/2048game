# 2048game
2048game on Terminal

2048ゲームの解法アルゴリズムを研究することもできます.

<div align="center">
<img src="/img/menu.png" width="60%">
</div>

## プレイモード:
1. N - ノーマルプレイ
2. A - オートプレイ (コンピュータがプレイ)
3. C - データ収集 (オートプレイを繰り返してスコアデータを収集　盤面は最終結果のみ)

## 実装アルゴリズム
右下に数字の大きなタイルを集めることをベースに,右・下・上の3方向に対して2手先まで盤面を予測し,そのスコアで次の方向を決定するアルゴリズムを実装しています.

(現在の平均スコア 14000 前後)
<div align="center">
<img src="/img/data.png" width="60%">
</div>

20000点を超えると2048タイルができていることを意味します.

## 実行方法:
1. `cd src/`
2. `make`
3. `./2048`
