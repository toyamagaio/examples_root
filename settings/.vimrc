"---------基本的な設定
colorscheme ron
set nocompatible                "viとの互換性をとらない
set fileformats=unix,dos,mac    "改行コードの認識
set vb t_vb=                    "ビープ音を鳴らさない
set backspace=indent,eol,start  "バックスペースキーで削除出きるものを指定
"indent:行頭の空白 elo: 改行 start:挿入モード開始位置より手前の文字

"---------バックアップ関係
set nobackup           "バックアップをとらない
set writebackup        "ファイルの上書き前にバックアップを作る、
"ただしbackupがon出ない限りバックアップは上書き成功後削除される

"--------検索関係
set history=100    "コマンド、検索パターンを100個まで履歴に残す
set ignorecase     "検索時に大文字小文字を区別しない
set smartcase      "検索時に大文字が含まれている場合は区別して検索
set wrapscan       "最後まで検索したら先頭に戻る
"set noincsearch    "インクリメンタルサーチを使わない
set incsearch    "インクリメンタルサーチを使

"---------表示関係
set title                             "タイトルをウィンドウ枠に表示
"set notitle                             "タイトルをウィンドウ枠に表示
"set nonumber                          "行番号を表示しない
set number                           "行番号を表示
set ruler                            "ルーラーを表示
"set list                              "タブ文字をCTRL-Iで表示し、行末に$で表示
set showcmd                           "入力中のコマンドをステータス表示に
set laststatus=2                      "ステータスラインを常に表示
set showmatch                         "括弧入力時の対応する括弧を表示
set matchtime=5                       "対応する括弧の表示時間を＊にする
syntax on                             "シンタックスハイライトを有効にする
set hlsearch                          "検索結果文字列のハイライトを有効
highlight Comment ctermfg=DarkCyan    "コメント文の色を変更
set wildmenu                          "コマンドライン補完を拡張モードにする
set textwidth=0                       "入力されているテキストの最大幅を無効に
set wrap                              "ウィンドウの幅より長い行は折り返して、次の行に続けて表示

highlight ZenkakuSpace cterm=underline ctermfg=lightblue guibg=darkgray
match ZenkakuSpace /　/  " 全角スペースの表示$

set statusline=%n\:%y%F\ \|%{(&fenc!=''?&fenc:&enc).'\|'.&ff.'\|'}%m%r%=<%l/%L:%p%%>  "ステータスラインに表示する情報の指定

highlight StatusLine   term=NONE cterm=NONE ctermfg=black ctermbg=white "ステータスラインの色

"set cursorline                        "カーソル行の強調表示

"----------インデント
"set noautoindent "オートインデントを無効
set tabstop=4       "タブが対応する空白の数
set softtabstop=4   "編集操作の時、タブが対応する空白の数
set shiftwidth=4    "インデントの各段階に使われる空白の数
set noexpandtab     "タブを挿入する時に代わりに空白を使わない

"----------国際化関係
"------文字コードの設定
set encoding=utf-8
set termencoding=utf-8
set fileencoding=utf-8
set fileencodings=ucs-bom,euc-jp,cp932,iso-2022-jp
set fileencodings+=,ucs-2le,ucs-2,utf-8

"-----------その他
set hidden         "バッファを切り替えてもundoの効力を失わない
set shortmess+=I   "起動時のメッセージを表示しない
