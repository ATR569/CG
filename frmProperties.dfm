object formProperties: TformProperties
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Propriedades do objeto'
  ClientHeight = 506
  ClientWidth = 841
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 456
    Width = 841
    Height = 50
    Align = alBottom
    Padding.Left = 10
    Padding.Top = 10
    Padding.Right = 10
    Padding.Bottom = 10
    TabOrder = 0
    ExplicitTop = 447
    ExplicitWidth = 808
    object btnCancel: TButton
      Left = 11
      Top = 11
      Width = 112
      Height = 28
      Align = alLeft
      Cancel = True
      Caption = 'Cancelar'
      ModalResult = 2
      TabOrder = 0
    end
    object btnOk: TButton
      Left = 718
      Top = 11
      Width = 112
      Height = 28
      Align = alRight
      Caption = 'Ok'
      Default = True
      ModalResult = 1
      TabOrder = 1
      ExplicitLeft = 685
    end
  end
  object Panel12: TPanel
    Left = 456
    Top = 0
    Width = 385
    Height = 456
    Align = alRight
    TabOrder = 1
    ExplicitLeft = 420
    object lstHistory: TListView
      AlignWithMargins = True
      Left = 4
      Top = 4
      Width = 377
      Height = 222
      Align = alClient
      Columns = <
        item
          Caption = 'Transforma'#231#227'o'
          Width = 200
        end
        item
          Caption = 'Refer'#234'ncia'
          Width = 100
        end>
      ColumnClick = False
      HideSelection = False
      HotTrack = True
      ReadOnly = True
      RowSelect = True
      TabOrder = 0
      ViewStyle = vsReport
      ExplicitLeft = 1
      ExplicitTop = 1
      ExplicitWidth = 347
      ExplicitHeight = 332
    end
    object Panel2: TPanel
      Left = 1
      Top = 342
      Width = 383
      Height = 113
      Align = alBottom
      BevelOuter = bvNone
      Color = clWhite
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Cambria Math'
      Font.Style = []
      Padding.Left = 5
      Padding.Top = 5
      Padding.Right = 5
      Padding.Bottom = 5
      ParentBackground = False
      ParentFont = False
      TabOrder = 1
      StyleElements = [seFont, seBorder]
      ExplicitTop = 333
      ExplicitWidth = 347
      object Label1: TLabel
        AlignWithMargins = True
        Left = 88
        Top = 8
        Width = 12
        Height = 97
        Align = alLeft
        Alignment = taCenter
        Caption = '='
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Cambria Math'
        Font.Style = []
        ParentFont = False
        Layout = tlCenter
        ExplicitLeft = 70
        ExplicitHeight = 89
      end
      object Label2: TLabel
        AlignWithMargins = True
        Left = 286
        Top = 8
        Width = 9
        Height = 97
        Align = alRight
        Alignment = taCenter
        Caption = 'X'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Cambria Math'
        Font.Style = []
        ParentFont = False
        Layout = tlCenter
        ExplicitLeft = 268
        ExplicitHeight = 89
      end
      object Panel3: TPanel
        AlignWithMargins = True
        Left = 20
        Top = 8
        Width = 50
        Height = 97
        Align = alLeft
        BevelOuter = bvNone
        TabOrder = 0
        object gridOrigem: TStringGrid
          Left = 0
          Top = 0
          Width = 50
          Height = 97
          Align = alClient
          BevelEdges = []
          BorderStyle = bsNone
          Color = clWhite
          ColCount = 1
          DefaultColWidth = 50
          DefaultRowHeight = 32
          DefaultDrawing = False
          FixedCols = 0
          RowCount = 3
          FixedRows = 0
          Options = []
          ScrollBars = ssNone
          TabOrder = 0
          ExplicitWidth = 33
        end
      end
      object Panel6: TPanel
        AlignWithMargins = True
        Left = 8
        Top = 8
        Width = 6
        Height = 97
        Align = alLeft
        BevelEdges = [beLeft, beTop, beBottom]
        BevelKind = bkTile
        BevelOuter = bvNone
        Ctl3D = False
        ParentCtl3D = False
        TabOrder = 1
        StyleElements = [seFont, seClient]
      end
      object Panel7: TPanel
        AlignWithMargins = True
        Left = 76
        Top = 8
        Width = 6
        Height = 97
        Align = alLeft
        BevelEdges = [beTop, beRight, beBottom]
        BevelKind = bkTile
        BevelOuter = bvNone
        Ctl3D = False
        ParentCtl3D = False
        TabOrder = 2
        StyleElements = [seFont, seClient]
        ExplicitLeft = 58
      end
      object Panel4: TPanel
        AlignWithMargins = True
        Left = 369
        Top = 8
        Width = 6
        Height = 97
        Align = alRight
        BevelEdges = [beTop, beRight, beBottom]
        BevelKind = bkTile
        BevelOuter = bvNone
        Ctl3D = False
        ParentCtl3D = False
        TabOrder = 3
        StyleElements = [seFont, seClient]
        ExplicitLeft = 345
        ExplicitTop = 11
      end
      object Panel8: TPanel
        AlignWithMargins = True
        Left = 313
        Top = 8
        Width = 50
        Height = 97
        Align = alRight
        BevelOuter = bvNone
        TabOrder = 4
        ExplicitLeft = 289
        object gridTarget: TStringGrid
          Left = 0
          Top = 0
          Width = 50
          Height = 97
          Align = alClient
          BevelEdges = []
          BorderStyle = bsNone
          Color = clWhite
          ColCount = 1
          DefaultColWidth = 50
          DefaultRowHeight = 32
          DefaultDrawing = False
          FixedCols = 0
          RowCount = 3
          FixedRows = 0
          Options = []
          ScrollBars = ssNone
          TabOrder = 0
          ExplicitLeft = 16
          ExplicitTop = -5
        end
      end
      object Panel9: TPanel
        AlignWithMargins = True
        Left = 301
        Top = 8
        Width = 6
        Height = 97
        Align = alRight
        BevelEdges = [beLeft, beTop, beBottom]
        BevelKind = bkTile
        BevelOuter = bvNone
        Ctl3D = False
        ParentCtl3D = False
        TabOrder = 5
        StyleElements = [seFont, seClient]
        ExplicitLeft = 283
      end
      object Panel5: TPanel
        AlignWithMargins = True
        Left = 106
        Top = 8
        Width = 6
        Height = 97
        Align = alLeft
        BevelEdges = [beLeft, beTop, beBottom]
        BevelKind = bkTile
        BevelOuter = bvNone
        Ctl3D = False
        ParentCtl3D = False
        TabOrder = 6
        StyleElements = [seFont, seClient]
        ExplicitLeft = 88
      end
      object Panel10: TPanel
        AlignWithMargins = True
        Left = 118
        Top = 8
        Width = 150
        Height = 97
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 7
        ExplicitLeft = 100
        object gridTransform: TStringGrid
          Left = 0
          Top = 0
          Width = 150
          Height = 97
          Align = alClient
          BevelEdges = []
          BorderStyle = bsNone
          Color = clWhite
          ColCount = 3
          DefaultColWidth = 50
          DefaultRowHeight = 32
          DefaultDrawing = False
          FixedCols = 0
          RowCount = 3
          FixedRows = 0
          Options = []
          ScrollBars = ssNone
          TabOrder = 0
          ExplicitWidth = 146
          ExplicitHeight = 93
        end
      end
      object Panel11: TPanel
        AlignWithMargins = True
        Left = 274
        Top = 8
        Width = 6
        Height = 97
        Align = alRight
        BevelEdges = [beTop, beRight, beBottom]
        BevelKind = bkTile
        BevelOuter = bvNone
        Ctl3D = False
        ParentCtl3D = False
        TabOrder = 8
        StyleElements = [seFont, seClient]
        ExplicitLeft = 256
      end
    end
    object lstPoints: TListView
      AlignWithMargins = True
      Left = 4
      Top = 232
      Width = 377
      Height = 107
      Align = alBottom
      Columns = <
        item
          Caption = 'Pontos'
          Width = 200
        end>
      ColumnClick = False
      HideSelection = False
      HotTrack = True
      ReadOnly = True
      RowSelect = True
      TabOrder = 2
      ViewStyle = vsReport
      ExplicitWidth = 341
    end
  end
  object desktop: TPanel
    AlignWithMargins = True
    Left = 3
    Top = 3
    Width = 450
    Height = 450
    Align = alClient
    BevelKind = bkFlat
    BevelOuter = bvNone
    Color = clWhite
    ParentBackground = False
    TabOrder = 2
    StyleElements = [seFont]
    ExplicitWidth = 453
    ExplicitHeight = 441
  end
end
