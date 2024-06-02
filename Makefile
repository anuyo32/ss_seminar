# 参考：https://qiita.com/harinez2/items/0d25eabdc6dae66e7bee

NAME        = ./bin/main
SRCDIR      = ./src
SRCS        = $(shell find $(SRCDIR) -name "*.cpp")
OBJS        = $(SRCS:.cpp=.o)
DEPENDS     = $(OBJS:.o=.d)
CXX         = g++

# コンパイラのオプション：https://jp.xlsoft.com/documents/intel/compiler/18/cpp_18_win_lin/GUID-F1391F3A-D995-4EBE-BBDA-9A07D601C2F3.html
CXXFLAGS    = -Wall -Wextra -std=c++20 -pedantic-errors -MMD -MP

.PHONY: all
all: $(NAME)

# 依存関係ファイルを読み込む
# -includeで、(初回実行時など)依存関係ファイルがなくてもMakefileの実行を続行
-include $(DEPENDS)

$(NAME): $(OBJS)
	mkdir -p ./bin
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

# コンパイルで生成されたオブジェクトファイル(.o)と依存関係ファイル(.d)を削除
.PHONY: clean
clean:
	rm -f $(OBJS) $(DEPENDS)

# 上記ファイルに加え、実行ファイルも削除
.PHONY: fclean
fclean: clean
	rm -f $(NAME)

# ビルドのやり直し
.PHONY: re
re: fclean all
