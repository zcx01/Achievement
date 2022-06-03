#!/usr/bin/env python3
# -*- coding: utf-8 -*-

class CBaseBlock(object):
    endl=""
    comment_separator="    "
    tab=' '*4
    def __init__(self,
                header,
                start_indent="",
                base_indent=' '*4,
                block_segmenter=('{','}'),
                comment_block=None,
                parent=None):

        self.data =[]
        self.content_start_line = 0
        self.start_indent = start_indent
        self.base_indent = base_indent
        self.block_segmenter = block_segmenter
        self.comment_block = comment_block     #For comment block that goes before the header
        self.parent_block = parent
        self.is_closed = False

        if isinstance(parent, CBaseBlock):
            self.start_indent = parent.start_indent + parent.base_indent
            self.base_indent  = parent.base_indent
        self.total_indent = self.start_indent + self.base_indent

        if header:
            self.data.append("{}{}{}".format(self.start_indent, header, CBaseBlock.endl))
            self.content_start_line += 1

        if block_segmenter[0]:
            self.data.append("{}{}{}".format(self.start_indent, block_segmenter[0], CBaseBlock.endl))
            self.content_start_line += 1

    def close(self):
        if self.is_closed == True:
            return
        self.is_closed = True
        if self.block_segmenter[1]:
            self.data.append("{}{}".format(self.start_indent, self.block_segmenter[1]))
        self.is_closed = True
        if getattr(self, "comment_block", None):
            self.comment_block.close()
            self.data = self.comment_block.data + self.data
        if self.parent_block:
            self.parent_block.add_block(self) #add the current block to its parent block.
        else:
            self.data.append(CBaseBlock.endl)
        ##### function end #####

    def __enter__(self):
        return self

    def __exit__(self, e_type, e_value, e_traceback):
        self.close()    #close the current block

    @staticmethod
    def _format_line(line, comment="", termination=";", comment_char="//", new_lines=1):
        """
        To format a line
        Args:
            line (str): The code line to be added
            comment (str): Comment for the line if any
            termination (str): Termination character for the code line
            comment_char (str): Comment tag
            new_lines (int): Number of new lines to be added after the line
        """
        if line:
            main_line = line + termination
        else:
            main_line = line

        # Only add comment if given
        if main_line and comment:
            if comment_char == '/**/':
                main_line += "{}/* {} */".format(CBaseBlock.comment_separator, comment)
            else:
                main_line += "{}{}{}".format(CBaseBlock.comment_separator, comment_char, comment)
        elif comment:
            main_line += "{}{}".format(comment_char, comment)
        return main_line + (CBaseBlock.endl * new_lines)

    def add_code_line(self, line, comment="", comment_char="//", termination=';', new_lines=1, position=None):
        formatted_line = self._format_line( line,
                                            comment=comment,
                                            comment_char=comment_char,
                                            termination=termination,
                                            new_lines=new_lines)
        if position is None or type(position) != int:
            self.data.append("{}{}".format(self.total_indent, formatted_line))
        else:
            self.data.insert(self.content_start_line+position, "{}{}".format(self.total_indent, formatted_line))


    def add_comment_line(self, comment="", new_lines=1):
        formatted_line = self._format_line( "",
                                            comment=comment,
                                            comment_char="//",
                                            termination="",
                                            new_lines=new_lines)
        self.data.append("{}{}".format(self.total_indent, formatted_line))

    def add_block_comment_line(self, comment="", new_lines=1):
        formatted_line = self._format_line( "",
                                            comment=comment,
                                            comment_char="/**/",
                                            termination="",
                                            new_lines=new_lines)
        self.data.append("{}{}".format(self.total_indent, formatted_line))

    def add_blank_line(self, number_of_lines=1):
        self.data.append(CBaseBlock.endl * number_of_lines)

    def add_base_block(self, block):
        self.data += block.data
        assert isinstance(block, CBaseBlock), "Incorrect data type given for base block"

    def add_comment_block(self, block):
        assert isinstance(block, CCommentBlock), "Incorrect data type given for comment block"
        self.comment_block = block

    def add_block(self, block):
        assert isinstance(block, (CBaseBlock, CCommentBlock)), "Incorrect data type give for block"
        self.data += block.data

class CCommentBlock(CBaseBlock):
    def __init__(self, start_indent="", block_segmenter=('/*','*/'), parent=None):
        super(CCommentBlock, self).__init__("",
                                start_indent=start_indent,
                                base_indent="",
                                block_segmenter=block_segmenter,
                                parent = parent)
    def add_line(self, line):
        self.data.append('{} * {}'.format(self.start_indent, line))

class CSwitchBlock(CBaseBlock):
    def __init__(self, switch_variable, block_segmenter=('{','}'), parent=None):
        header = "switch ({switch_variable})".format(**locals())
        tmp_block_segmenter = block_segmenter
        #  super(CSwitchBlock, self).__init__(header, block_segmenter = tmp_block_segmenter, parent=parent)
        super().__init__(header, block_segmenter = tmp_block_segmenter, parent=parent)

class CSwitchCase(CBaseBlock):
    def __init__(self, case_const, block_segmenter=("", "{}break;".format(CBaseBlock.tab)), comment_block=None, parent=None):
        header = "case {case_const}:".format(**locals()) if case_const != 'default' else 'default:'
        tmp_block_segmenter = block_segmenter
        tmp_comment_block   = comment_block
        #  super(CSwitchCase, self).__init__(header,  block_segmenter = tmp_block_segmenter, parent=parent)
        super().__init__(header,  block_segmenter = tmp_block_segmenter, comment_block=tmp_comment_block, parent=parent)

