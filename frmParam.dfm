object formParam: TformParam
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Par'#226'metros'
  ClientHeight = 335
  ClientWidth = 268
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
  object pnlParams: TPanel
    AlignWithMargins = True
    Left = 10
    Top = 10
    Width = 248
    Height = 96
    Margins.Left = 10
    Margins.Top = 10
    Margins.Right = 10
    Margins.Bottom = 10
    Align = alTop
    BevelKind = bkFlat
    BevelOuter = bvNone
    Padding.Left = 5
    Padding.Top = 5
    Padding.Right = 5
    Padding.Bottom = 5
    TabOrder = 0
    DesignSize = (
      244
      92)
    object edtParamX: TLabeledEdit
      Left = 115
      Top = 8
      Width = 119
      Height = 21
      Alignment = taRightJustify
      Anchors = [akLeft, akTop, akRight]
      CharCase = ecUpperCase
      EditLabel.Width = 100
      EditLabel.Height = 13
      EditLabel.Caption = 'Deslocamento em X: '
      LabelPosition = lpLeft
      MaxLength = 7
      TabOrder = 0
      Text = '0,000'
      OnExit = fixValues
      OnKeyPress = edtParamXKeyPress
    end
    object edtParamY: TLabeledEdit
      Left = 115
      Top = 35
      Width = 119
      Height = 21
      Alignment = taRightJustify
      Anchors = [akLeft, akTop, akRight]
      CharCase = ecUpperCase
      EditLabel.Width = 100
      EditLabel.Height = 13
      EditLabel.Caption = 'Deslocamento em Y: '
      LabelPosition = lpLeft
      MaxLength = 7
      TabOrder = 1
      Text = '0,000'
      OnExit = fixValues
      OnKeyPress = edtParamXKeyPress
    end
    object edtParamZ: TLabeledEdit
      Left = 115
      Top = 62
      Width = 119
      Height = 21
      Alignment = taRightJustify
      Anchors = [akLeft, akTop, akRight]
      CharCase = ecUpperCase
      EditLabel.Width = 100
      EditLabel.Height = 13
      EditLabel.Caption = 'Deslocamento em Z: '
      LabelPosition = lpLeft
      MaxLength = 7
      TabOrder = 2
      Text = '0,000'
      OnExit = fixValues
      OnKeyPress = edtParamXKeyPress
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 285
    Width = 268
    Height = 50
    Align = alBottom
    Padding.Left = 10
    Padding.Top = 10
    Padding.Right = 10
    Padding.Bottom = 10
    TabOrder = 3
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
      Left = 145
      Top = 11
      Width = 112
      Height = 28
      Align = alRight
      Caption = 'Ok'
      Default = True
      ModalResult = 1
      TabOrder = 1
      OnClick = btnOkClick
    end
  end
  object rdgReference: TRadioGroup
    AlignWithMargins = True
    Left = 10
    Top = 116
    Width = 248
    Height = 94
    Margins.Left = 10
    Margins.Top = 0
    Margins.Right = 10
    Align = alTop
    Caption = 'Referencial'
    ItemIndex = 0
    Items.Strings = (
      'Origem'
      'Centro do Objeto'
      'Ponto espec'#237'fico')
    TabOrder = 1
    OnClick = rdgReferenceClick
  end
  object grpRefPoint: TGroupBox
    AlignWithMargins = True
    Left = 10
    Top = 213
    Width = 248
    Height = 67
    Margins.Left = 10
    Margins.Top = 0
    Margins.Right = 10
    Margins.Bottom = 5
    Align = alClient
    Caption = 'Ponto de Refer'#234'ncia'
    TabOrder = 2
    Visible = False
    DesignSize = (
      248
      67)
    object edtX: TLabeledEdit
      Left = 10
      Top = 31
      Width = 71
      Height = 21
      Alignment = taCenter
      Anchors = [akLeft, akTop, akRight]
      CharCase = ecUpperCase
      EditLabel.Width = 6
      EditLabel.Height = 13
      EditLabel.Caption = 'X'
      MaxLength = 7
      TabOrder = 0
      Text = '0,000'
      OnExit = fixValues
      OnKeyPress = edtParamXKeyPress
    end
    object edtY: TLabeledEdit
      Left = 87
      Top = 31
      Width = 71
      Height = 21
      Alignment = taCenter
      Anchors = [akLeft, akTop, akRight]
      CharCase = ecUpperCase
      EditLabel.Width = 6
      EditLabel.Height = 13
      EditLabel.Caption = 'Y'
      MaxLength = 7
      TabOrder = 1
      Text = '0,000'
      OnExit = fixValues
      OnKeyPress = edtParamXKeyPress
    end
    object edtZ: TLabeledEdit
      Left = 165
      Top = 31
      Width = 71
      Height = 21
      Alignment = taCenter
      Anchors = [akLeft, akTop, akRight]
      CharCase = ecUpperCase
      EditLabel.Width = 6
      EditLabel.Height = 13
      EditLabel.Caption = 'Z'
      MaxLength = 7
      TabOrder = 2
      Text = '0,000'
      OnExit = fixValues
      OnKeyPress = edtParamXKeyPress
    end
  end
end
