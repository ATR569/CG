object formProperties: TformProperties
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Propriedades do objeto'
  ClientHeight = 532
  ClientWidth = 847
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 482
    Width = 847
    Height = 50
    Align = alBottom
    Padding.Left = 10
    Padding.Top = 10
    Padding.Right = 10
    Padding.Bottom = 10
    TabOrder = 0
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
      Left = 724
      Top = 11
      Width = 112
      Height = 28
      Align = alRight
      Caption = 'Ok'
      Default = True
      ModalResult = 1
      TabOrder = 1
    end
  end
  object Panel12: TPanel
    AlignWithMargins = True
    Left = 459
    Top = 3
    Width = 385
    Height = 450
    Align = alRight
    TabOrder = 1
    object lstHistory: TListView
      AlignWithMargins = True
      Left = 4
      Top = 84
      Width = 377
      Height = 137
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
    end
    object Panel2: TPanel
      Left = 1
      Top = 337
      Width = 383
      Height = 112
      Align = alBottom
      BevelOuter = bvNone
      Color = 15590354
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
      object Label1: TLabel
        AlignWithMargins = True
        Left = 88
        Top = 8
        Width = 12
        Height = 96
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
        ExplicitHeight = 89
      end
      object Label2: TLabel
        AlignWithMargins = True
        Left = 286
        Top = 8
        Width = 9
        Height = 96
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
        ExplicitHeight = 89
      end
      object Panel3: TPanel
        AlignWithMargins = True
        Left = 20
        Top = 8
        Width = 50
        Height = 96
        Align = alLeft
        BevelOuter = bvNone
        TabOrder = 0
        object gridNewPoint: TStringGrid
          Left = 0
          Top = 0
          Width = 50
          Height = 96
          Align = alClient
          BevelEdges = []
          BorderStyle = bsNone
          ColCount = 1
          DefaultColWidth = 50
          DefaultRowHeight = 32
          DrawingStyle = gdsClassic
          FixedColor = 15590354
          FixedCols = 0
          RowCount = 4
          FixedRows = 3
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'Cambria Math'
          Font.Style = []
          GradientEndColor = clWhite
          Options = [goFixedRowClick]
          ParentColor = True
          ParentFont = False
          ScrollBars = ssNone
          TabOrder = 0
          StyleElements = [seClient]
        end
      end
      object Panel6: TPanel
        AlignWithMargins = True
        Left = 8
        Top = 8
        Width = 6
        Height = 96
        Align = alLeft
        BevelEdges = [beLeft, beTop, beBottom]
        BevelKind = bkTile
        BevelOuter = bvNone
        Ctl3D = True
        ParentCtl3D = False
        TabOrder = 1
      end
      object Panel7: TPanel
        AlignWithMargins = True
        Left = 76
        Top = 8
        Width = 6
        Height = 96
        Align = alLeft
        BevelEdges = [beTop, beRight, beBottom]
        BevelKind = bkTile
        BevelOuter = bvNone
        Ctl3D = True
        ParentCtl3D = False
        TabOrder = 2
      end
      object Panel4: TPanel
        AlignWithMargins = True
        Left = 369
        Top = 8
        Width = 6
        Height = 96
        Align = alRight
        BevelEdges = [beTop, beRight, beBottom]
        BevelKind = bkTile
        BevelOuter = bvNone
        Ctl3D = True
        ParentCtl3D = False
        TabOrder = 3
      end
      object Panel8: TPanel
        AlignWithMargins = True
        Left = 313
        Top = 8
        Width = 50
        Height = 96
        Align = alRight
        BevelOuter = bvNone
        TabOrder = 4
        object gridOldPoint: TStringGrid
          Left = 0
          Top = 0
          Width = 50
          Height = 96
          Align = alClient
          BevelEdges = []
          BorderStyle = bsNone
          ColCount = 1
          DefaultColWidth = 50
          DefaultRowHeight = 32
          DrawingStyle = gdsClassic
          FixedColor = 15590354
          FixedCols = 0
          RowCount = 4
          FixedRows = 3
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'Cambria Math'
          Font.Style = []
          GradientEndColor = clWhite
          Options = []
          ParentColor = True
          ParentFont = False
          ScrollBars = ssNone
          TabOrder = 0
        end
      end
      object Panel9: TPanel
        AlignWithMargins = True
        Left = 301
        Top = 8
        Width = 6
        Height = 96
        Align = alRight
        BevelEdges = [beLeft, beTop, beBottom]
        BevelKind = bkTile
        BevelOuter = bvNone
        Ctl3D = True
        ParentCtl3D = False
        TabOrder = 5
      end
      object Panel5: TPanel
        AlignWithMargins = True
        Left = 106
        Top = 8
        Width = 6
        Height = 96
        Align = alLeft
        BevelEdges = [beLeft, beTop, beBottom]
        BevelKind = bkTile
        BevelOuter = bvNone
        Ctl3D = True
        ParentCtl3D = False
        TabOrder = 6
      end
      object Panel10: TPanel
        AlignWithMargins = True
        Left = 118
        Top = 8
        Width = 150
        Height = 96
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 7
        object gridTransform: TStringGrid
          Left = 0
          Top = 0
          Width = 150
          Height = 96
          Align = alClient
          BevelEdges = []
          BorderStyle = bsNone
          ColCount = 3
          DefaultColWidth = 50
          DefaultRowHeight = 32
          DrawingStyle = gdsClassic
          FixedColor = 15590354
          FixedCols = 0
          RowCount = 4
          FixedRows = 3
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'Cambria Math'
          Font.Style = []
          GradientEndColor = clWhite
          Options = []
          ParentColor = True
          ParentFont = False
          ScrollBars = ssNone
          TabOrder = 0
        end
      end
      object Panel11: TPanel
        AlignWithMargins = True
        Left = 274
        Top = 8
        Width = 6
        Height = 96
        Align = alRight
        BevelEdges = [beTop, beRight, beBottom]
        BevelKind = bkTile
        BevelOuter = bvNone
        Ctl3D = True
        ParentCtl3D = False
        TabOrder = 8
      end
    end
    object lstPoints: TListView
      AlignWithMargins = True
      Left = 4
      Top = 227
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
    end
    object GroupBox1: TGroupBox
      AlignWithMargins = True
      Left = 4
      Top = 4
      Width = 377
      Height = 74
      Align = alTop
      Caption = 'Propriedades'
      TabOrder = 3
      object Label3: TLabel
        Left = 24
        Top = 21
        Width = 70
        Height = 13
        Caption = 'Cor do objeto:'
      end
      object Label4: TLabel
        Left = 24
        Top = 48
        Width = 129
        Height = 13
        Caption = 'Algoritmo de Rasteriza'#231#227'o:'
      end
      object cmbColor: TColorBox
        Left = 160
        Top = 16
        Width = 145
        Height = 22
        Style = [cbStandardColors, cbPrettyNames]
        TabOrder = 0
        OnChange = cmbColorChange
      end
      object cmbDrawMethod: TComboBox
        Left = 160
        Top = 44
        Width = 145
        Height = 21
        Style = csDropDownList
        ItemIndex = 0
        TabOrder = 1
        Text = 'Bresenham'
        OnChange = cmbDrawMethodChange
        Items.Strings = (
          'Bresenham'
          'DDA'
          'Polinomial'
          'Trigonom'#233'trico')
      end
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
    ParentShowHint = False
    ShowHint = True
    TabOrder = 2
    StyleElements = [seFont]
    OnMouseMove = desktopMouseMove
  end
  object pnlCoord: TPanel
    Left = 0
    Top = 456
    Width = 847
    Height = 26
    Align = alBottom
    BevelEdges = []
    BevelOuter = bvNone
    Padding.Left = 20
    Padding.Right = 20
    TabOrder = 3
    object lblUserX: TLabel
      AlignWithMargins = True
      Left = 384
      Top = 0
      Width = 70
      Height = 26
      Margins.Left = 0
      Margins.Top = 0
      Margins.Right = 0
      Margins.Bottom = 0
      Align = alLeft
      AutoSize = False
      Caption = 'X'
      Layout = tlCenter
      ExplicitLeft = 403
    end
    object lblUserY: TLabel
      AlignWithMargins = True
      Left = 454
      Top = 0
      Width = 70
      Height = 26
      Margins.Left = 0
      Margins.Top = 0
      Margins.Right = 0
      Margins.Bottom = 0
      Align = alLeft
      AutoSize = False
      Caption = 'Y'
      Layout = tlCenter
      ExplicitLeft = 608
    end
    object lblScrX: TLabel
      AlignWithMargins = True
      Left = 139
      Top = 0
      Width = 51
      Height = 26
      Margins.Left = 0
      Margins.Top = 0
      Margins.Right = 0
      Margins.Bottom = 0
      Align = alLeft
      AutoSize = False
      Caption = 'X'
      Layout = tlCenter
    end
    object lblScrY: TLabel
      AlignWithMargins = True
      Left = 190
      Top = 0
      Width = 51
      Height = 26
      Margins.Left = 0
      Margins.Top = 0
      Margins.Right = 0
      Margins.Bottom = 0
      Align = alLeft
      AutoSize = False
      Caption = 'Y'
      Layout = tlCenter
    end
    object Label5: TLabel
      AlignWithMargins = True
      Left = 249
      Top = 0
      Width = 135
      Height = 26
      Margins.Left = 0
      Margins.Top = 0
      Margins.Right = 0
      Margins.Bottom = 0
      Align = alLeft
      AutoSize = False
      Caption = 'Coordenadas de Usu'#225'rio:'
      GlowSize = 10
      Layout = tlCenter
      ExplicitLeft = 395
    end
    object Label6: TLabel
      AlignWithMargins = True
      Left = 20
      Top = 0
      Width = 119
      Height = 26
      Margins.Left = 0
      Margins.Top = 0
      Margins.Right = 0
      Margins.Bottom = 0
      Align = alLeft
      AutoSize = False
      Caption = 'Coordenadas de Tela:'
      GlowSize = 10
      Layout = tlCenter
    end
    object Bevel1: TBevel
      AlignWithMargins = True
      Left = 244
      Top = 3
      Width = 2
      Height = 20
      Align = alLeft
      Shape = bsLeftLine
      ExplicitLeft = 321
      ExplicitTop = 6
    end
  end
  object timer: TTimer
    Interval = 1
    OnTimer = timerTimer
    Left = 800
    Top = 14
  end
end
