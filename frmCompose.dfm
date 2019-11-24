object formCompose: TformCompose
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Transforma'#231#227'o Composta'
  ClientHeight = 509
  ClientWidth = 344
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    AlignWithMargins = True
    Left = 3
    Top = 319
    Width = 338
    Height = 19
    Align = alBottom
    Caption = 'Matriz Resultante'
    Color = clHotLight
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    ExplicitTop = 325
    ExplicitWidth = 120
  end
  object Panel1: TPanel
    Left = 0
    Top = 459
    Width = 344
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
      Left = 221
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
  object lstHistory: TListView
    AlignWithMargins = True
    Left = 3
    Top = 37
    Width = 338
    Height = 276
    Align = alClient
    Columns = <
      item
        Caption = 'Transforma'#231#227'o'
        Width = 250
      end>
    ColumnClick = False
    HideSelection = False
    HotTrackStyles = [htHandPoint]
    ReadOnly = True
    RowSelect = True
    TabOrder = 1
    ViewStyle = vsReport
    ExplicitHeight = 282
  end
  object Panel2: TPanel
    AlignWithMargins = True
    Left = 3
    Top = 344
    Width = 338
    Height = 112
    Align = alBottom
    BevelOuter = bvNone
    Color = 15590354
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Cambria Math'
    Font.Style = []
    Padding.Left = 82
    Padding.Top = 5
    Padding.Right = 82
    Padding.Bottom = 5
    ParentBackground = False
    ParentFont = False
    TabOrder = 2
    StyleElements = [seFont, seBorder]
    ExplicitLeft = 0
    ExplicitTop = 347
    ExplicitWidth = 344
    object Panel5: TPanel
      AlignWithMargins = True
      Left = 85
      Top = 8
      Width = 6
      Height = 96
      Align = alLeft
      BevelEdges = [beLeft, beTop, beBottom]
      BevelKind = bkTile
      BevelOuter = bvNone
      Ctl3D = True
      ParentCtl3D = False
      TabOrder = 0
    end
    object Panel10: TPanel
      AlignWithMargins = True
      Left = 97
      Top = 8
      Width = 144
      Height = 96
      Align = alClient
      BevelOuter = bvNone
      TabOrder = 1
      ExplicitWidth = 150
      object gridTransform: TStringGrid
        Left = 0
        Top = 0
        Width = 144
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
        ExplicitWidth = 150
        ColWidths = (
          50
          50
          50)
      end
    end
    object Panel11: TPanel
      AlignWithMargins = True
      Left = 247
      Top = 8
      Width = 6
      Height = 96
      Align = alRight
      BevelEdges = [beTop, beRight, beBottom]
      BevelKind = bkTile
      BevelOuter = bvNone
      Ctl3D = True
      ParentCtl3D = False
      TabOrder = 2
      ExplicitLeft = 253
    end
  end
  object barTransformations: TToolBar
    AlignWithMargins = True
    Left = 3
    Top = 3
    Width = 338
    Height = 28
    AutoSize = True
    BorderWidth = 1
    ButtonHeight = 24
    ButtonWidth = 24
    Caption = 'barTools'
    Images = formMain.imagelist16
    ParentShowHint = False
    ShowHint = True
    TabOrder = 3
    object btnTranslate: TToolButton
      Left = 0
      Top = 0
      ImageIndex = 3
      OnClick = btnTranslateClick
    end
    object btnScale: TToolButton
      Left = 24
      Top = 0
      ImageIndex = 4
      OnClick = btnScaleClick
    end
    object btnRotate: TToolButton
      Left = 48
      Top = 0
      ImageIndex = 5
      OnClick = btnRotateClick
    end
    object btnShear: TToolButton
      Left = 72
      Top = 0
      ImageIndex = 6
      OnClick = btnShearClick
    end
    object btnReflect: TToolButton
      Left = 96
      Top = 0
      ImageIndex = 7
      OnClick = btnReflectClick
    end
    object ToolButton2: TToolButton
      AlignWithMargins = True
      Left = 120
      Top = 0
      Width = 8
      Caption = 'ToolButton2'
      ImageIndex = 11
      Style = tbsDivider
    end
    object btnDelete: TToolButton
      Left = 128
      Top = 0
      Caption = 'Delete'
      ImageIndex = 10
      OnClick = btnDeleteClick
    end
  end
end
